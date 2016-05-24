/// <reference path="../../alarm-clock.d.ts" />
/// <reference path="./googleCalendar.d.ts" />

import * as express from "express-serve-static-core";
import settings from "../settings";
import * as passport from "passport";
import * as async from "async";
import cache from "../cache";
var GoogleStrategy = require('passport-google-oauth').OAuth2Strategy;
var gcal = require('google-calendar');
var refresh = require('passport-oauth2-refresh');

const CACHE_EVENTS_KEY = 'googleCalendar/events';

export default function (app:express.Application) {
  const config:GoogleCalendarSettings = settings().get('googleCalendar');

  var strategy = new GoogleStrategy({
      clientID: config.clientId,
      clientSecret: config.clientSecret,
      callbackURL: 'http://localhost:8080/googleCalendar/auth/callback',
      scope: ['openid', 'email', 'https://www.googleapis.com/auth/calendar']
    },
    (accessToken, refreshToken, profile, done) => {
      profile.accessToken = accessToken;
      profile.refreshToken = refreshToken;
      return done(null, profile);
    });
  passport.use(strategy);
  refresh.use(strategy);

  app.get('/googleCalendar/auth',
    passport.authenticate('google', {session: false, accessType: 'offline'})
  );

  app.get('/googleCalendar/auth/callback',
    passport.authenticate('google', {session: false, failureRedirect: '/'}),
    function (req:express.Request, res:express.Response, next:express.NextFunction) {
      req.session['access_token'] = req.user.accessToken;
      req.session['refresh_token'] = req.user.refreshToken;
      res.redirect('/');
    }
  );

  function refreshAccessTokens(req:express.Request, callback:(err?:Error)=>void) {
    refresh.requestNewAccessToken('google', req.session['refresh_token'], function (err, newAccessToken, refreshToken) {
      if (err) {
        return callback(err);
      }
      req.session['access_token'] = newAccessToken;
      req.session['refresh_token'] = refreshToken;
      return callback();
    });
  }

  app.get('/googleCalendar/auth/refresh', function (req:express.Request, res:express.Response, next:express.NextFunction) {
    if (!req.session || !req.session['refresh_token']) {
      console.error('missing "refresh_token" in session');
      return res.sendStatus(401);
    }

    refreshAccessTokens(req, function (err) {
      if (err) {
        return next(err);
      }
      return res.send('OK');
    });
  });

  app.get('/googleCalendar/calendarList', function (req:express.Request, res:express.Response, next:express.NextFunction) {
    if (!req.session || !req.session['access_token']) {
      return res.sendStatus(401);
    }

    gcal(req.session['access_token']).calendarList.list((err, data) => {
      if (err) {
        return next(err);
      }
      res.send(data);
    })
  });

  app.get('/googleCalendar/:calendarId/events', function (req:express.Request, res:express.Response, next:express.NextFunction) {
    const calendarId = req.params.calendarId;
    if (!req.session || !req.session['access_token']) {
      return res.sendStatus(401);
    }

    getEventsForCalendar(req.session['access_token'], calendarId, function (err, data) {
      if (err) {
        return next(err);
      }
      res.send(data);
    });
  });

  app.get('/googleCalendar/events', function (req:express.Request, res:express.Response, next:express.NextFunction) {
    if (!req.session || !req.session['access_token']) {
      return res.sendStatus(401);
    }

    cache().get(CACHE_EVENTS_KEY, 60 * 1000, (callback) => {
      async.mapSeries(config.calendars, function (calendarId, callback) {
        getEventsForCalendar(req.session['access_token'], calendarId, (err, events) => {
          if (err) {
            return refreshAccessTokens(req, (err?: Error) => {
              if (err) {
                return callback(err, null);
              }
              return getEventsForCalendar(req.session['access_token'], calendarId, callback);
            });
          }
          return callback(null, events);
        });
      }, function (err, results:GoogleCalendarEventsResponse[]) {
        if (err) {
          if (err.code == 401) {
            return res.sendStatus(401);
          }
          return callback(err);
        }
        var allEvents = combineEvents(results);
        var v:GoogleCalendarEventsResponse = {
          items: allEvents
        };
        return callback(null, JSON.stringify(v));
      });
    }, (err, value) => {
      if (err) {
        return next(err);
      }
      return res.send(JSON.parse(value));
    });
  });

  function combineEvents(results:GoogleCalendarEventsResponse[]) {
    var allEvents:GoogleCalendarEvent[] = [];
    results.forEach((result) => {
      result.items.forEach((item) => {
        allEvents.push(item);
      });
    });
    allEvents = allEvents.sort((a, b) => {
      var aStart = a.start.dateTime || a.start.date;
      var bStart = b.start.dateTime || b.start.date;
      return aStart.localeCompare(bStart);
    });
    return allEvents;
  }

  function getEventsForCalendar(accessToken:string, calendarId:string, callback:(err:Error, data?:GoogleCalendarEventsResponse) => void):void {
    const options = {
      orderBy: 'startTime',
      timeMin: toISODateString(new Date()),
      singleEvents: true,
      maxResults: 25
    };
    gcal(accessToken).events.list(calendarId, options, (err, data) => {
      if (err) {
        console.error('Could not get calendar events (calendarId: ' + calendarId + ', options: ' + JSON.stringify(options) + ')', err);
        return callback(err);
      }
      var res:GoogleCalendarEventsResponse = data as GoogleCalendarEventsResponse;
      res.items.forEach((item) => {
        item.calendarId = calendarId;
      });
      return callback(null, res);
    });
  }

  function toISODateString(d) {
    function pad(n) {
      return n < 10 ? '0' + n : n
    }

    return d.getUTCFullYear() + '-'
      + pad(d.getUTCMonth() + 1) + '-'
      + pad(d.getUTCDate()) + 'T'
      + pad(d.getUTCHours()) + ':'
      + pad(d.getUTCMinutes()) + ':'
      + pad(d.getUTCSeconds()) + 'Z'
  }
}
