import * as React from "react";
import {WundergroundConditions, WundergroundForecast, WundergroundService} from "../services/WundergroundService";

const DEGREES = '\xB0';

export interface WundergroundBaseProps {
    wundergroundService: WundergroundService
}

export interface WundergroundBaseState {
    conditions?: WundergroundConditions,
    forecast?: WundergroundForecast
}

export default class WundergroundBase<TProps extends WundergroundBaseProps, TState extends WundergroundBaseState> extends React.Component<TProps, TState> {
    conditionsUpdatedListener;
    forecastUpdatedListener;

    componentDidMount() {
        this.conditionsUpdatedListener = this.onConditionsUpdated.bind(this);
        this.props.wundergroundService.addConditionsUpdatedListener(this.conditionsUpdatedListener);

        this.forecastUpdatedListener = this.onForecastUpdated.bind(this);
        this.props.wundergroundService.addForecastUpdatedListener(this.forecastUpdatedListener);
    }

    componentWillUnmount() {
        this.props.wundergroundService.removeConditionsUpdatedListener(this.conditionsUpdatedListener);
        this.props.wundergroundService.removeForecastUpdatedListener(this.forecastUpdatedListener);
    }

    protected onConditionsUpdated(conditions: WundergroundConditions) {
        const state: any = {conditions: conditions};
        this.setState(state);
    }

    protected onForecastUpdated(forecast: WundergroundForecast) {
        const state: any = {forecast: forecast};
        this.setState(state);
    }

    protected getTemperature(): string {
        if (!this.state.conditions) {
            return 'NA';
        }
        return this.state.conditions.current_observation.temp_f + DEGREES + ' F';
    }

    protected getIcon(): string {
        if (!this.state.conditions) {
            return '/wunderground/na.gif';
        }
        return '/wunderground/' + this.state.conditions.current_observation.icon + '.gif';
    }

    protected getIconAlt(): string {
        if (!this.state.conditions) {
            return 'NA';
        }
        return this.state.conditions.current_observation.weather;
    }

    protected getForecastTemperature(idx: number): string {
        if (!this.state.forecast) {
            return 'NA';
        }
        let day = this.state.forecast.forecast.simpleforecast.forecastday[idx];
        if (!day) {
            return 'NA';
        }
        return day.low.fahrenheit + DEGREES + '/' + day.high.fahrenheit + DEGREES;
    }

    protected getForecastDay(idx: number) {
        if (!this.state.forecast) {
            return null;
        }
        if (new Date().getHours() > 20) {
            idx++;
        }
        return this.state.forecast.forecast.simpleforecast.forecastday[idx];
    }

    protected getForecastIcon(idx: number): string {
        const day = this.getForecastDay(idx);
        if (!day) {
            return '/wunderground/na.gif';
        }
        return '/wunderground/' + day.icon + '.gif';
    }

    protected getForecastIconAlt(idx: number): string {
        const day = this.getForecastDay(idx);
        if (!day) {
            return 'NA';
        }
        return day.conditions;
    }

    protected getForecastWeekday(idx: number): string {
        const day = this.getForecastDay(idx);
        if (!day) {
            return 'NA';
        }
        return day.date.weekday_short;
    }
}
