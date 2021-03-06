import * as express from 'express-serve-static-core';
import wunderground from './wunderground';
import googleCalendar from './googleCalendar';
import cache from '../cache';

export default function (app: express.Application) {
    app.get('/cache/clear', (req, res, next) => {
        cache().clear((err) => {
            if (err) {
                return next(err);
            }
            res.send('OK');
        });
    });

    wunderground(app);
    googleCalendar(app);
}
