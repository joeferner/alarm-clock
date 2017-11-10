import * as React from "react";
import {CSSProperties} from "react";
import * as Radium from "radium";

@Radium
export default class Back extends React.Component<any, any> {
    styles = {
        container: {
            position: 'absolute',
            top: '0px',
            left: '0px',
            cursor: 'pointer',
            opacity: 0.1
        } as CSSProperties
    };

    static onClick() {
        window.history.back();
    }

    render() {
        return (
            <div style={this.styles.container}>
                <img onClick={Back.onClick} src='/back.png'/>
            </div>
        )
    }
}
