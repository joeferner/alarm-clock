.PHONY: clean all

all: build build-web

build: typings/typings-install node_modules/npm-install
	cd src && ../node_modules/.bin/tsc

build-web: typings/typings-install node_modules/npm-install
	cd web/src && ../../node_modules/.bin/webpack --progress

typings/typings-install: tsd.json
	tsd install
	touch typings/typings-install

node_modules/npm-install: package.json
	npm install
	touch node_modules/npm-install

clean:
	rm -rf node_modules build build-web
