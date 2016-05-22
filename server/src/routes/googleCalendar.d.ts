
interface GoogleCalendarSettings {
  clientId: string,
  clientSecret: string,
  calendars: string[]
}

interface GoogleCalendarEvent {
  calendarId: string,
  id: string,
  summary: string,
  start: {
    date?: string,
    dateTime?: string
  }
}

interface GoogleCalendarEventsResponse {
  items: GoogleCalendarEvent[]
}
