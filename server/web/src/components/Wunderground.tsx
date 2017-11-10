import * as React from "react";
import WundergroundBase, {WundergroundBaseProps, WundergroundBaseState} from "./WundergroundBase";
import * as Radium from "radium";

const DEGREES = '\xB0';

interface WundergroundProps extends WundergroundBaseProps {
}

interface WundergroundState extends WundergroundBaseState {
}

@Radium
export default class Wunderground extends WundergroundBase<WundergroundProps, WundergroundState> {
    styles = {
        container: {
            marginLeft: 'auto'
        },

        table: {
            width: '100%'
        },

        dayContainer: {
            margin: '5px',
            textAlign: 'center'
        },

        image: {
            width: '50px',
            height: '50px'
        },

        temperature: {
            textAlign: 'center'
        },

        weekday: {
            textAlign: 'center'
        }
    };

    state: WundergroundState = {};

    private static expandSelf() {
        window.location.hash = 'wunderground';
    }

    render() {
        return (<div style={this.styles.container} onClick={() => Wunderground.expandSelf()}>
            <table style={this.styles.table}>
                <tbody>
                <tr>
                    <td style={this.styles.dayContainer}>
                        <img style={this.styles.image} src={this.getIcon()} alt={this.getIconAlt()}/>
                        <div style={this.styles.temperature}>{this.getTemperature()}</div>
                        <div style={this.styles.weekday}>Current</div>
                    </td>
                    {[0, 1].map((x, i) =>
                        <td key={'forcast-' + i} style={this.styles.dayContainer}>
                            <img style={this.styles.image} src={this.getForecastIcon(i)}
                                 alt={this.getForecastIconAlt(i)}/>
                            <div style={this.styles.temperature}>{this.getForecastTemperature(i)}</div>
                            <div style={this.styles.weekday}>{this.getForecastWeekday(i)}</div>
                        </td>
                    )}
                </tr>
                </tbody>
            </table>
        </div>)
    }
}
