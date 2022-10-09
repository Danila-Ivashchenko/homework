obj = {}
obj[false] = 'str'
obj[2] = 'str'
obj[{}] = 'str'

sym = Symbol('Some symbol')

obj[sym] = 'new'

console.log(obj)

document.write(sym.description)


function addSym(v){
    v[Symbol('Pseudo private')] = 7
}

const obj2 = {prop : 'world'}
addSym(obj2)

console.log(obj2[Reflect.ownKeys(obj2)[1]])

Object.defineProperty(obj,
    'myKey', {
        enumerable: false,
        value: 365
    })
console.log(Object.keys(obj), Reflect.ownKeys(obj))