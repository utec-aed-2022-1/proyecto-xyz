const axios = require('axios')

const url = 'http://localhost:8000'

export const userLogin = async ({ dni, password }) => {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (dni === '12345678' && password === 'password') {
        resolve()
      } else {
        reject()
      }
    }, 3000)
  })
}

export const userRegister = async ({ dni, name, password }) => {
  console.log('userRegister')
  axios
    .post(`${url}/user`, {
      dni: dni,
      name: name,
      password: password
    })
    .then(function (response) {
      console.log(response)
      return response
    })
    .catch(function (error) {
      console.log(error)
      return error
    })
}
