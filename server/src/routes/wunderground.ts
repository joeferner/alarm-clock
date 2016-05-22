/// <reference path="../../alarm-clock.d.ts" />
import * as express from 'express-serve-static-core';
import * as axios from 'axios';
import settings from '../settings';
import cache from '../cache';

const CACHE_TTL = 10 * 60 * 1000;
const CACHE_CONDITIONS_KEY = '/wunderground/conditions';
const CACHE_FORECAST_KEY = '/wunderground/forecast';

function getConditionsUrl() {
  var wuSettings = settings().get('wunderground');
  return 'http://api.wunderground.com/api/' + wuSettings.key + '/conditions/q/' + wuSettings.location + '.json';
}

function getForecastUrl() {
  var wuSettings = settings().get('wunderground');
  return 'http://api.wunderground.com/api/' + wuSettings.key + '/forecast/q/' + wuSettings.location + '.json';
}

function getWundergroundJsonUrl(
  cacheKey: string,
  url: string,
  req: express.Request,
  res: express.Response,
  next: express.NextFunction
) {
  var missingFn = function (callback) {
    console.log('requesting', url);
    return axios.get(url)
      .then((body) => {
        console.log('success: ' + url + ' (status: ' + body.status + ')');
        try {
          return callback(null, JSON.stringify(body.data));
        } catch(e) {
          console.error('failed to parse json:', body.data);
          return callback(e);
        }
      })
      .catch((err) => {
        console.error('could not get url: ' + url, err);
        return callback(err);
      })
  };
  var conditions = cache().get(cacheKey, CACHE_TTL, missingFn, (err, value) => {
    if (err) {
      console.error('failed to request', url, err);
      return next(err);
    }
    return res.send(JSON.parse(value));
  });
}

export default function(app: express.Application) {
  app.get('/wunderground/conditions', getWundergroundJsonUrl.bind(this, CACHE_CONDITIONS_KEY, getConditionsUrl()));
  app.get('/wunderground/forecast', getWundergroundJsonUrl.bind(this, CACHE_FORECAST_KEY, getForecastUrl()));
}
