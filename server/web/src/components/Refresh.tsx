import * as React from "react";
import {CSSProperties} from "react";
import * as Radium from "radium";

@Radium
export default class Refresh extends React.Component<any, any> {
    styles = {
        container: {
            position: 'absolute',
            top: '0px',
            right: '0px',
            cursor: 'pointer',
            opacity: 0.1
        } as CSSProperties
    };

    static onClick() {
        location.reload();
    }

    render() {
        return (
            <div style={this.styles.container}>
                <img onClick={Refresh.onClick} src='/refresh.png'/>
            </div>
        )
    }
}
