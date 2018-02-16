/**
* @copyright 2018 - Max Bebök
* @author Max Bebök
* @license GNU-GPLv3 - see the "LICENSE" file in the root directory
*/

let png = require("./bindings.js");
const fs = require("fs");

let width = 10;
let height = 10;
let colorValues = Buffer.alloc(width * height * 4);

let i=0;
for(let y=0; y<height; ++y)
{
    for(let x=0; x<width; ++x)
    {
        colorValues[i++] = x + y;
        colorValues[i++] = x * 10;
        colorValues[i++] = y * 10;
        colorValues[i++] = 255;
    }
}

let pngBuffer = png.encode(colorValues, width, height);
console.log(pngBuffer);

fs.writeFileSync("test.png", pngBuffer);
