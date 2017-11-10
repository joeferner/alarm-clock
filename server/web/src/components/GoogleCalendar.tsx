import * as React from "react";
import {CSSProperties} from "react";
import * as Radium from "radium";
import {GoogleCalendarEvent, GoogleCalendarEventsResponse} from "../models/GoogleCalendarTypes";
import axios from "axios";

const dateFormat = require('dateformat');

interface GoogleCalendarProps {
}

interface GoogleCalendarState {
    items?: GoogleCalendarEvent[];
    unauthorized?: boolean;
}

@Radium
export default class GoogleCalendar extends React.Component<GoogleCalendarProps, GoogleCalendarState> {
    updateEventsInterval;

    styles = {
        authorizeContainer: {
            textAlign: 'center'
        } as CSSProperties,

        authorizeLink: {
            color: 'white'
        } as CSSProperties,

        container: {
            overflowY: 'scroll',
            overflowX: 'hidden'
        } as CSSProperties,

        list: {
            width: '240px'
        } as CSSProperties,

        line: {},

        day: {
            fontWeight: 'bold',
            borderBottom: '1px solid white'
        } as CSSProperties,

        time: {
            fontWeight: 'bold',
            marginRight: '5px',
            textAlign: 'right',
            whiteSpace: 'nowrap',
            width: '70px'
        } as CSSProperties,

        summary: {},

        summaryDiv: {
            whiteSpace: 'nowrap',
            textOverflow: 'ellipsis',
            overflow: 'hidden',
            width: '150px'
        } as CSSProperties
    };

    state = {
        items: [],
        unauthorized: false
    };

    componentDidMount() {
        this.updateEventsInterval = setInterval(this.updateEvents.bind(this), 10 * 60 * 1000);
        this.updateEvents();
    }

    componentWillUnmount() {
        clearInterval(this.updateEventsInterval);
    }

    updateEvents() {
        axios.get('/googleCalendar/events')
            .then((body) => {
                const res: GoogleCalendarEventsResponse = body.data as GoogleCalendarEventsResponse;
                this.setState({
                    items: res.items,
                    unauthorized: false
                });
            })
            .catch((err) => {
                console.error('Could not get events', err);
                this.setState({items: []});
                if (err.status == 401) {
                    this.setState({unauthorized: true});
                }
            });
    }

    private static getEventDateTime(item: GoogleCalendarEvent): Date {
        const dateTimeString = item.start.dateTime || item.start.date;
        return this.parseDateString(dateTimeString);
    }

    private static parseDateString(str: string): Date {
        let date;
        const m = str.match(/^([0-9]+)-([0-9]+)-([0-9]+)$/);
        if (m) {
            date = new Date(parseInt(m[1]), parseInt(m[2]) - 1, parseInt(m[3]));
        } else {
            date = new Date(Date.parse(str));
        }
        return date;
    }

    static getEventDateTimeString(item: GoogleCalendarEvent): string {
        const date = GoogleCalendar.getEventDateTime(item);
        if (item.start.dateTime) {
            return dateFormat(date, 'h:mmtt');
        } else {
            return 'All day';
        }
    }

    private groupItemsByDay() {
        const groups = {};
        this.state.items.forEach((item) => {
            const yearMonthDay = dateFormat(GoogleCalendar.getEventDateTime(item), 'yyyy-mm-dd');
            let group = groups[yearMonthDay];
            if (!group) {
                group = [];
                groups[yearMonthDay] = group;
            }
            group.push(item);
        });
        return groups;
    }

    render() {
        if (this.state.unauthorized) {
            return (
                <div style={this.styles.authorizeContainer}>
                    <a style={this.styles.authorizeLink} href="/googleCalendar/auth">Authorize Calendar</a>
                </div>
            );
        } else {
            return (
                <div style={this.styles.container}>
                    <table style={this.styles.list}>
                        <tbody>
                        {this.renderListItems()}
                        </tbody>
                    </table>
                </div>
            );
        }
    }

    renderListItems() {
        const groups = this.groupItemsByDay();
        return Object.keys(groups).sort().map((groupName) => {
            return this.renderGroup(groupName, groups[groupName]);
        });
    }

    renderGroup(yearMonthDay, items) {
        const date = GoogleCalendar.parseDateString(yearMonthDay);
        const yearMonthDayString = dateFormat(date, 'dddd mmm dd');

        const header = (
            <tr style={this.styles.line} key={yearMonthDay}>
                <td style={this.styles.day} colSpan={2}>{yearMonthDayString}</td>
            </tr>
        );

        return [header, items.map((item: GoogleCalendarEvent) => {
            return (
                <tr style={this.styles.line} key={item.id}>
                    <td style={this.styles.time}>{GoogleCalendar.getEventDateTimeString(item)}</td>
                    <td style={this.styles.summary}>
                        <div style={this.styles.summaryDiv}>{item.summary}</div>
                    </td>
                </tr>
            );
        })];
    }
}
