/**
* @copyright 2018 - Max Bebök
* @author Max Bebök
* @license GNU-GPLv3 - see the "LICENSE" file in the root directory
*/

const fs = require("fs");
const assert = require('assert');
var expect = require('chai').expect;
let png = require("./../bindings.js");

describe('PNG encoding', () =>
{
    describe('error handling', () =>
    {
        it('no params', function() 
        { 
            expect(() => png.encode()).throws("Argument 1 is not a Buffer");
        });

        it('missing param (1)', function() 
        { 
            expect(() => png.encode(Buffer.from([]))).throws();
        });

        it('missing param (2)', function() 
        { 
            expect(() => png.encode(Buffer.from([]), 42)).throws();
        });

        it('size too big', function() 
        { 
            expect(() => png.encode(Buffer.from([1,2,3,4]), 100, 100)).throws("Buffer size does not match the width and height");
        });
    });

    describe('encoding', () =>
    {
        it('simple PNG with colors', function() 
        {   
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

            let generatedBuffer = png.encode(colorValues, width, height);
            const testBuffer = fs.readFileSync("./tests/colors.png");
            
            assert(generatedBuffer.compare(testBuffer) == 0);
        });
    });
});
