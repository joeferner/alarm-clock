import * as express from "express-serve-static-core";
import axios from "axios";
import settings from "../settings";
import cache from "../cache";

const CACHE_TTL = 10 * 60 * 1000;
const CACHE_CONDITIONS_KEY = '/wunderground/conditions';
const CACHE_FORECAST_KEY = '/wunderground/forecast';
const CACHE_RADAR_KEY = '/wunderground/radar.png';

function getConditionsUrl() {
    const wuSettings = settings().get('wunderground');
    return 'http://api.wunderground.com/api/' + wuSettings.key + '/conditions/q/' + wuSettings.location + '.json';
}

function getForecastUrl() {
    const wuSettings = settings().get('wunderground');
    return 'http://api.wunderground.com/api/' + wuSettings.key + '/forecast/q/' + wuSettings.location + '.json';
}

function getRadarUrl() {
    const wuSettings = settings().get('wunderground');
    return 'http://api.wunderground.com/api/' + wuSettings.key + '/radar/q/' + wuSettings.location + '.png?newmaps=1&height=200';
}

function getWundergroundJsonUrl(
    cacheKey: string,
    url: string,
    req: express.Request,
    res: express.Response,
    next: express.NextFunction
) {
    const missingFn = function (callback) {
        console.log('requesting', url);
        return axios.get(url)
            .then((body) => {
                console.log('success: ' + url + ' (status: ' + body.status + ')');
                try {
                    return callback(null, JSON.stringify(body.data));
                } catch (e) {
                    console.error('failed to parse json:', body.data);
                    return callback(e);
                }
            })
            .catch((err) => {
                console.error('could not get url: ' + url, err);
                return callback(err);
            })
    };
    cache().get(cacheKey, CACHE_TTL, missingFn, (err, value) => {
        if (err) {
            console.error('failed to request', url, err);
            return next(err);
        }
        return res.send(JSON.parse(value));
    });
}

function getWundergroundImageUrl(
    cacheKey: string,
    url: string,
    req: express.Request,
    res: express.Response,
    next: express.NextFunction
) {
    const missingFn = function (callback) {
        console.log('requesting', url);
        return axios.get(url, {responseType: 'arraybuffer'})
            .then((body) => {
                console.log('success: ' + url + ' (status: ' + body.status + ')');
                var bin: any = body.data;
                return callback(null, new Buffer(bin).toString('hex'));
            })
            .catch((err) => {
                console.error('could not get url: ' + url, err);
                return callback(err);
            })
    };
    cache().get(cacheKey, CACHE_TTL, missingFn, (err, value) => {
        if (err) {
            console.error('failed to request', url, err);
            return next(err);
        }
        res.writeHead(200, {'Content-Type': 'image/png'});
        return res.end(new Buffer(value, 'hex'), 'binary');
    });
}

export default function (app: express.Application) {
    app.get('/wunderground/conditions', getWundergroundJsonUrl.bind(this, CACHE_CONDITIONS_KEY, getConditionsUrl()));
    app.get('/wunderground/forecast', getWundergroundJsonUrl.bind(this, CACHE_FORECAST_KEY, getForecastUrl()));
    app.get('/wunderground/radar.png', getWundergroundImageUrl.bind(this, CACHE_RADAR_KEY, getRadarUrl()));
}
