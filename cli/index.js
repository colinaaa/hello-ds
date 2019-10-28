const sec = require("./src/sections");

const inquirer = require("inquirer");

const addon = require("./build/Release/dscliaddon.node");

// inquirer.prompt(sec).catch(e => console.log(e));
console.log(addon);
