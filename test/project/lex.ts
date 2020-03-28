interface TestCase {
  input: string;
  want: string;
}

const cases: TestCase[] = [];

const push = (input: string, want: string) => {
  cases.push({input, want});
};

push('123', 'Num');
push('0xff   sdf', 'Num');
push('abcd', 'Id');
push('int', 'Id');
push('while', 'Id');
push('for', 'Id');
push('enum', 'Id');
push('char', 'Id');
push('=', 'Assign');
push('+', 'Add');
push('>', 'Gt');
push('<', 'Lt');
push('>=', 'Ge');
push('<=', 'Le');
push('>>', 'Shr');
push('<<', 'Shl');
push('|', 'Or');
push('&', 'And');
push('^', 'Xor');
push('&&', 'Lan');
push('||', 'Lor');
push('*', 'Mul');
push('%', 'Mod');
push('?', 'Cond');
push('-', 'Sub');
push('--', 'Dec');
push('++', 'Inc');
push('!=', 'Ne');
push('==', 'Eq');
push('/', 'Div');

console.log(JSON.stringify(cases, null, 4));
