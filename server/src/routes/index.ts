/// <reference path="../../alarm-clock.d.ts" />
import * as express from 'express-serve-static-core';
import wunderground from './wunderground';

export default function(app: express.Application) {
  wunderground(app);
}
