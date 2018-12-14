const exec = require('child_process').exec;
const fs = require('fs');
const extract = require('extract-zip');
const request = require('request');
const editJsonFile = require("edit-json-file");

var name = 'EASYPT';
var cmd;
var archiveUrl;
var archiveDir = __dirname + '/bin.zip';
var binDir = __dirname + '/bin';

switch (process.platform) {
    case 'linux':
        var file = editJsonFile(`${process.env.HOME}/.config/Code/User/settings.json`);
        file.set('easypt.executablePath',  __dirname + '/bin/easypt');
        file.save();
        archiveUrl = 'https://ci.appveyor.com/api/projects/antollo/easypt/artifacts/artifacts.zip?branch=master&job=Image%3A%20Ubuntu';
        break;
    case 'win32':
        var file = editJsonFile(`${process.env.APPDATA}\\Code\\User\\settings.json`);
        file.set('easypt.executablePath',  __dirname + '\\bin\\easypt.exe');
        file.save();
        archiveUrl = 'https://ci.appveyor.com/api/projects/antollo/easypt/artifacts/artifacts.zip?branch=master&job=Image%3A%20Visual%20Studio%202017';
        break;
    default:
        process.exit();
        break;
}

request({ url: archiveUrl, encoding: null }, (err, resp, body) => {
    if (err) throw err;
    fs.writeFile(archiveDir, body, (err) => {
        if (err) throw err;
        extract(archiveDir, { dir: binDir }, (err) => {
            if (err) throw err;
            fs.unlink(archiveDir, (err) => {
                if (err) throw err;
            });
        });
    });
});
