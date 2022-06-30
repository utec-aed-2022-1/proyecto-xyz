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
  const options = {
    headers: {
      'Access-Control-Allow-Origin': '*',
      'Content-Type': 'application/json',
      'Access-Control-Allow-Headers':
        'Origin, X-Requested-With, Content-Type, Accept'
    }
  }
  axios
    .post(
      `${url}/user`,
      {
        dni: dni,
        name: name,
        password: password
      },
      options
    )
    .then(function (response) {
      console.log(response)
      return response
    })
    .catch(function (error) {
      console.log(error)
      return error
    })
}
