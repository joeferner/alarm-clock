/// <reference path="../alarm-clock.d.ts" />
import fs = require('fs');
import path = require('path');
  
interface CacheEntry {
  value: string;
  expireTime: number;
}

export interface CacheGetCallbackFn {
  (err: Error, value?: string): void;
}

export interface CacheMissingFn {
  (callback: (err: Error, value?: string) => void): void;
}

function createCacheEntry(value: string, ttl: number): CacheEntry {
  return {
    value: value,
    expireTime: new Date().getTime() + ttl 
  }
}

function isExpired(cacheEntry: CacheEntry): boolean {
  return new Date().getTime() > cacheEntry.expireTime;
}

export class Cache {
  cache: any;
  cacheFilename: string;
  
  constructor(cacheFilename: string) {
    this.cacheFilename = cacheFilename;
    this.readCacheSync();
  }
  
  readCacheSync(): void {
    if (fs.existsSync(this.cacheFilename)) {
      var data = fs.readFileSync(this.cacheFilename, 'utf8');
      try {
        this.cache = JSON.parse(data);
      } catch(e) {
        console.error('Could not parse cache file: ', data, e);
        this.cache = {};
      }
    } else {
      console.log('Cache file "' + this.cacheFilename + '" missing');
      this.cache = {};
    }
  }
  
  writeCache(callback: (err?: Error) => void): void {
    try {
      fs.writeFileSync(this.cacheFilename, JSON.stringify(this.cache));
      return callback();
    } catch(e) {
      console.error('could not write cache file', e);
      return callback(e);
    }
  }
  
  clear(callback: (err?: Error) => void): void {
    this.cache = {};
    this.writeCache(callback);
  }
  
  get(name: string, ttl: number, missingFn: CacheMissingFn, callback: CacheGetCallbackFn): any {
    var cacheEntry: CacheEntry = this.cache[name];
    if (!cacheEntry || isExpired(cacheEntry)) {
      console.log('cache miss ' + name + ' (expired: ' + (cacheEntry == null ? 'no' : 'yes') + ')')
      return missingFn((err, value) => {
        if (err) {
          return callback(err);
        }
        this.cache[name] = createCacheEntry(value, ttl);
        return this.writeCache((err) => {
          if (err) {
            return callback(err);
          }
          return callback(null, value);
        });
      });
    }
    console.log('cache hit ' + name);
    return this.writeCache((err) => {
      if (err) {
        return callback(err);
      }
      return callback(null, cacheEntry.value);
    });
  }
}

var cache: Cache = new Cache(path.join(__dirname, '../cache.json'));

export default function getCache(): Cache {
  return cache;
}