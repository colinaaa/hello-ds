const ops = [
  "clear list",
  "get length",
  "get elements",
  "locate elements",
  "prior elements",
  "next element",
  "insert element",
  "delete element",
  "tranverse"
];
const questions = [
  {
    type: "confirm",
    name: "init",
    message: "init the list?",
    default: true
  },
  {
    type: "rawlist",
    name: "operation",
    message: "What do you want to do?",
    choices: ops,
    filter: function(val) {
      return val.toLowerCase();
    }
  },
  {
    type: "input",
    name: "quantity",
    message: "How many do you need?",
    validate: function(value) {
      var valid = !isNaN(parseFloat(value));
      return valid || "Please enter a number";
    },
    filter: Number
  },
  {
    type: "expand",
    name: "toppings",
    message: "What about the toppings?",
    choices: [
      {
        key: "p",
        name: "Pepperoni and cheese",
        value: "PepperoniCheese"
      },
      {
        key: "a",
        name: "All dressed",
        value: "alldressed"
      },
      {
        key: "w",
        name: "Hawaiian",
        value: "hawaiian"
      }
    ]
  },
  {
    type: "rawlist",
    name: "beverage",
    message: "You also get a free 2L beverage",
    choices: ["Pepsi", "7up", "Coke"]
  },
  {
    type: "input",
    name: "comments",
    message: "Any comments on your purchase experience?",
    default: "Nope, all good!"
  },
  {
    type: "list",
    name: "prize",
    message: "For leaving a comment, you get a freebie",
    choices: ["cake", "fries"],
    when: function(answers) {
      return answers.comments !== "Nope, all good!";
    }
  }
];

module.exports = questions;