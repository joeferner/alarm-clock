/// <reference path="../../alarm-clock.d.ts" />
import * as express from 'express-serve-static-core';
import request = require('request');
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
    return request(url, function (err, reqres, body) {
      if (err) {
        return callback(err);
      }
      try {
        JSON.parse(body);
      } catch(e) {
        return callback(e);
      }
      return callback(null, body);
    });
  };
  var conditions = cache().get(cacheKey, CACHE_TTL, missingFn, (err, value) => {
    if (err) {
      return next(err);
    }
    return res.send(JSON.parse(value));
  });
}

export default function(app: express.Application) {
  app.get('/wunderground/conditions', getWundergroundJsonUrl.bind(this, CACHE_CONDITIONS_KEY, getConditionsUrl()));
  app.get('/wunderground/forecast', getWundergroundJsonUrl.bind(this, CACHE_FORECAST_KEY, getForecastUrl()));
}
