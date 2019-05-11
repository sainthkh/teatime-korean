const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const outputDir = path.join(__dirname, 'build/');
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const TerserJSPlugin = require('terser-webpack-plugin');
const OptimizeCSSAssetsPlugin = require('optimize-css-assets-webpack-plugin');
const CopyPlugin = require('copy-webpack-plugin');
const Fiber = require('fibers');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/Index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    filename: 'Index.js'
  },
  module: {
    rules: [{
      test: /\.scss$/,
      use: [{
        loader: process.env.NODE_ENV !== 'production' 
          ? 'style-loader' 
          : MiniCssExtractPlugin.loader,
      }, {
        loader: 'css-loader'
      }, {
        loader: 'sass-loader',
        options: {
          implementation: require('sass'),
          fiber: Fiber,
        }
      }]
    }]
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: 'src/index.html',
      inject: false
    }),
    new MiniCssExtractPlugin({
      filename: `styles/[name].css`
    }),
    new CopyPlugin([
      { from: 'src/server.html', to: 'server.html' },
    ]),
  ],
  optimization: {
    minimizer: [new TerserJSPlugin({}), new OptimizeCSSAssetsPlugin({})],
  },
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true
  }
};
