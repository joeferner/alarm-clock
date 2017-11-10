var webpack = require('webpack');
var WebpackNotifierPlugin = require('webpack-notifier');
var path = require('path');

module.exports = {
    devtool: 'eval',
    entry: './index.tsx',
    output: {
        path: path.resolve(__dirname, '../../build-web'),
        filename: 'bundle.js',
        sourceMapFilename: 'bundle.js.map',
        publicPath: '/'
    },
    plugins: [
        new webpack.NoEmitOnErrorsPlugin(),
        new WebpackNotifierPlugin({alwaysNotify: true})
    ],
    module: {
        loaders: [
            {
                test: /\.js|\.jsx$/,
                exclude: /node_modules/,
                loader: 'babel-loader',
                query: {
                    "presets": ["react", "es2015", "stage-0"]
                }
            },
            {
                test: /\.ts|\.tsx$/,
                loader: 'awesome-typescript-loader'
            }
        ]
    },
    resolve: {
        extensions: ['.js', '.jsx', '.ts', '.tsx']
    }
};
