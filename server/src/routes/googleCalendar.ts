/// <reference path="../../alarm-clock.d.ts" />
import * as express from 'express-serve-static-core';
import * as expressSession from 'express-session';
import * as axios from 'axios';
import settings from '../settings';
import cache from '../cache';
import * as passport from 'passport';
var GoogleStrategy = require('passport-google-oauth').OAuth2Strategy;
var gcal = require('google-calendar');

export default function(app: express.Application) {
  const config = settings().get('googleCalendar');
  
  passport.use(new GoogleStrategy({
      clientID: config.clientId,
      clientSecret: config.clientSecret,
      callbackURL: 'http://localhost:8080/googleCalendar/auth/callback',
      scope: ['openid', 'email', 'https://www.googleapis.com/auth/calendar']
    },
    (accessToken, refreshToken, profile, done) => {
      profile.accessToken = accessToken;
      return done(null, profile);
    })
  );
  
  app.get('/googleCalendar/auth',
    passport.authenticate('google', { session: false })
  );
  
  app.get('/googleCalendar/auth/callback',
    passport.authenticate('google', { session: false, failureRedirect: '/' }),
    function(req: express.Request, res: express.Response, next: express.NextFunction) {
      req.session['access_token'] = req.user.accessToken;
      res.redirect('/');
    }
  );

  app.get('/googleCalendar/events', function(req: express.Request, res: express.Response, next: express.NextFunction) {
    if (!req.session || !req.session['access_token']) {
      return res.redirect('/googleCalendar/auth');
    }
    
    gcal(req.session['access_token']).calendarList.list((err, data) => {
      console.log(err, data);
      res.send('OK');
    })
  });
}
