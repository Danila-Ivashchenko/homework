const str = 'gggghhhhwwwwwrrrrrjj'

function zip(str){
    out = ''
    n = 1
    for(let i = 0; i < str.length; i++){
        if (str[i+1] != str[i]){
                out += str[i] + n
                n = 1
            }
        else
            n += 1
    }
    return out
}

function unzip(str){
    out = ''
    n = ''
    char = ''
    for(let i = 0; i < str.length; i++){
        if ((str[i] < '0' || str[i] > '9') && n != ''){
            out += char.repeat(parseInt(n))
            n = ''
            char = ''
        }
        if (str[i] < '0' || str[i] > '9'){
            char = str[i]
        }
        else{
            n += str[i]
        }
    }
    out += char.repeat(parseInt(n))
    return out
    
}

document.write(zip(str), ' ', unzip(zip(str)))