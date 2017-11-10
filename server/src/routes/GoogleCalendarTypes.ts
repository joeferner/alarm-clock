export interface GoogleCalendarSettings {
    clientId: string,
    clientSecret: string,
    calendars: string[]
}

export interface GoogleCalendarEvent {
    calendarId: string,
    id: string,
    summary: string,
    start: {
        date?: string,
        dateTime?: string
    }
}

export interface GoogleCalendarEventsResponse {
    items: GoogleCalendarEvent[]
}
