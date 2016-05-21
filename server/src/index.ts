/// <reference path="../alarm-clock.d.ts" />
import express = require('express');
import routes from './routes';
import path  = require('path');

let PORT = 8080;

function startServer(callback) {
  let app = express();
  routes(app);
  app.use(express.static(path.join('web/static')));
  app.use(express.static(path.join('build-web')));
  app.listen(PORT, callback)
}

startServer((err) => {
  if (err) {
    console.error('Could not start server', err);
  }
  console.log('listening on http://localhost:' + PORT);
});
