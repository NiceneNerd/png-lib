var png;

if(process.env.DEBUG){
    png= require('./build/Debug/png.node')
}else{
    png= require('./build/Release/png.node')
}

module.exports = png;
