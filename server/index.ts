import express = require('express');
import routes from './routes';

let PORT = 8080;

function startServer(callback) {
  let app = express();
  routes(app);
  app.listen(PORT, callback)
}

startServer((err) => {
  if (err) {
    console.error('Could not start server', err);
  }
  console.log('listening on http://localhost:' + PORT);
});
