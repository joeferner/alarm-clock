var webpack = require('webpack')
var WebpackNotifierPlugin = require('webpack-notifier');

module.exports = {
  devtool: 'eval',
  entry: './index.tsx',
  output: {
    path: '../../build-web',
    filename: 'bundle.js',
    sourceMapFilename: 'bundle.js.map',
    publicPath: '/'
  },
  plugins: [
    new webpack.optimize.OccurenceOrderPlugin(),
    new webpack.NoErrorsPlugin(),
    new WebpackNotifierPlugin({alwaysNotify: true})
  ],
  module: {
    loaders: [
      {
        test: /\.js|\.jsx$/,
        exclude: /node_modules/,
        loader: 'babel',
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
    extensions: ['', '.js', '.jsx', '.ts', '.tsx']
  }
};
