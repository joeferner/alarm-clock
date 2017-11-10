import express = require('express');
import path  = require('path');
import * as expressSession from "express-session";
import * as cookieParser from "cookie-parser";
import * as bodyParser from "body-parser";
import routes from "./routes";
import * as passport from "passport";

const sessionFileStore = require("session-file-store");

let PORT = 8080;

function startServer(callback) {
    const fileStore = sessionFileStore(expressSession);

    let app = express();
    app.use(cookieParser());
    app.use(bodyParser.urlencoded({extended: true}));
    app.use(expressSession({
        store: new fileStore(),
        secret: 'alarm-clock',
        resave: false,
        saveUninitialized: true,
        cookie: {
            expires: new Date(253402300000000) // Approximately Fri, 31 Dec 9999 23:59:59 GMT
        }
    }));
    app.use(passport.initialize());

    routes(app);
    app.use(express.static(path.join(__dirname, '../../web/static')));
    app.use(express.static(path.join(__dirname, '../../build-web')));
    app.use(function (req: express.Request, res: express.Response, next: express.NextFunction) {
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
