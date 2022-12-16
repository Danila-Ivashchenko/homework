api_url = "https://fakestoreapi.com/products"


function sendRequest_2(method, url, body = null){
    return fetch(url, 
        {method, 
         body, 
         headers : {
            'Content-Type': 'application/json'
        }
    }).then(response => {
         return response.json() 
    })
}


function sendRequest(method, url, body = null){
    
    // resolve(result) - вызывается при успешном выполнении
    // reject(result) - вызывается при неудачном выполнении
    return new Promise((resolve, reject) => {
        const xhr = new XMLHttpRequest()
        xhr.open(method, url)
        xhr.responseType = 'json'
        xhr.setRequestHeader('Content-Type', 'application/json')

        xhr.onload = () => {
            if (xhr.status >= 400) {
                console.error("error");
                return
            }
            resolve(xhr.response)
        }
        
        xhr.onerror = () => {
            reject(xhr.response)
        }
        // xhr.send()

        xhr.send(JSON.stringify(body))
    })

    
}

const p = {
    title: 'test product',
    price: 13.5,
    description: 'lorem ipsum set',
    image: 'https://i.pravatar.cc',
    category: 'electronic'
}


sendRequest_2('POST', api_url, p)
    .then(data => console.log('success', data))
    // .catch(error => console.log('error', error))