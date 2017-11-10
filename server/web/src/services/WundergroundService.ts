import axios from 'axios';

export interface WundergroundConditions {
    current_observation: {
        weather: string,
        temp_f: number,
        icon: string,
        icon_url: string
    }
}

export interface WundergroundForecastSimpleForecastForecastDay {
    date: {
        year: number,
        month: number,
        day: number,
        weekday_short: string
    },
    period: number,
    high: {
        fahrenheit: string,
        celsius: string
    },
    low: {
        fahrenheit: string,
        celsius: string
    },
    conditions: string,
    icon: string,
    icon_url: string
}

export interface WundergroundForecast {
    forecast: {
        simpleforecast: {
            forecastday: WundergroundForecastSimpleForecastForecastDay[]
        }
    }
}

export interface ConditionsUpdatedListener {
    (conditions: WundergroundConditions): void
}

export interface ForecastUpdatedListener {
    (forecast: WundergroundForecast): void
}

export class WundergroundService {
    private conditionsUpdatedListeners: ConditionsUpdatedListener[] = [];
    private forecastUpdatedListeners: ForecastUpdatedListener[] = [];
    private conditions;
    private forecast;

    constructor() {
        setInterval(this.updateConditions.bind(this), 60 * 1000);
        this.updateConditions();

        setInterval(this.updateForecast.bind(this), 60 * 1000);
        this.updateForecast();
    }

    addConditionsUpdatedListener(listener: ConditionsUpdatedListener) {
        this.conditionsUpdatedListeners.push(listener);
        setTimeout(() => listener(this.conditions), 0);
    }

    addForecastUpdatedListener(listener: ForecastUpdatedListener) {
        this.forecastUpdatedListeners.push(listener);
        setTimeout(() => listener(this.forecast), 0);
    }

    removeConditionsUpdatedListener(listener: ConditionsUpdatedListener) {
        const i = this.conditionsUpdatedListeners.indexOf(listener);
        if (i >= 0) {
            this.conditionsUpdatedListeners = this.conditionsUpdatedListeners.splice(i, 1);
        }
    }

    removeForecastUpdatedListener(listener: ForecastUpdatedListener) {
        const i = this.forecastUpdatedListeners.indexOf(listener);
        if (i >= 0) {
            this.forecastUpdatedListeners = this.forecastUpdatedListeners.splice(i, 1);
        }
    }

    private dispatchConditionsUpdatedListeners(conditions: WundergroundConditions) {
        this.conditions = conditions;
        this.conditionsUpdatedListeners.forEach((fn) => {
                try {
                    fn(conditions)
                } catch (e) {
                    console.error('error in listener: ', fn, conditions, e);
                }
            }
        );
    }

    private dispatchForecastUpdatedListeners(forecast: WundergroundForecast) {
        this.forecast = forecast;
        this.forecastUpdatedListeners.forEach((fn) => {
            try {
                fn(forecast)
            } catch (e) {
                console.error('error in listener: ', fn, forecast, e);
            }
        });
    }

    updateConditions() {
        axios.get('/wunderground/conditions')
            .then((body) => {
                try {
                    var conditions: WundergroundConditions = body.data as WundergroundConditions;
                    this.dispatchConditionsUpdatedListeners(conditions);
                } catch (e) {
                    console.error('Could not parse conditions: ', body, e);
                    this.dispatchConditionsUpdatedListeners(null);
                }
            })
            .catch((err) => {
                console.error('Could not get conditions', err);
                this.dispatchConditionsUpdatedListeners(null);
            });
    }

    updateForecast() {
        axios.get('/wunderground/forecast')
            .then((body) => {
                try {
                    var forecast: WundergroundForecast = body.data as WundergroundForecast;
                    this.dispatchForecastUpdatedListeners(forecast);
                } catch (e) {
                    console.error('Could not parse forecast: ', body, e);
                    this.dispatchForecastUpdatedListeners(null);
                }
            })
            .catch((err) => {
                console.error('Could not get forecast', err);
                this.dispatchForecastUpdatedListeners(null);
            });
    }
}
