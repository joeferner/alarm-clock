/// <reference path="../alarm-clock.d.ts" />
import express = require('express');
import * as expressSession from 'express-session';
import * as cookieParser from 'cookie-parser'
import * as bodyParser from 'body-parser'
import routes from './routes';
import path  = require('path');
import * as passport from 'passport';

let PORT = 8080;

function startServer(callback) {
  let app = express();
  app.use(cookieParser());
  app.use(bodyParser.urlencoded({ extended: true }));
  app.use(expressSession({
    secret: 'alarm-clock',
    resave: false,
    saveUninitialized: true
  }));
  app.use(passport.initialize());

  routes(app);
  app.use(express.static(path.join(__dirname, '../web/static')));
  app.use(express.static(path.join(__dirname, '../build-web')));
  app.use(function(req: express.Request, res: express.Response, next: express.NextFunction) {
    console.log('Invalid path: ' + req.originalUrl);
    next();
  });
  app.listen(PORT, callback)
}

startServer((err) => {
  if (err) {
    console.error('Could not start server', err);
  }
  console.log('listening on http://localhost:' + PORT);
});
