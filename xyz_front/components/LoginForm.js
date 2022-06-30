/* eslint-disable react/no-unescaped-entities */
import React, { useState, useEffect } from 'react'

import {
  FormControl,
  FormLabel,
  Input,
  Container,
  Box,
  Button,
  CircularProgress,
  Text,
  Link,
  Heading
} from '@chakra-ui/react'

import { userLogin, userRegister } from '../src/utils/loginApi'
import ErrorMessage from './ErrorMessage'

import axios from 'axios'

const LoginForm = () => {
  const [dni, setDni] = useState('')
  const [name, setName] = useState('')
  const [password, setPassword] = useState('')
  const [error, setError] = useState('')
  const [isLoading, setIsLoading] = useState(false)
  const [registerForm, setRegisterForm] = useState(0)

  const [user, getUser] = useState('')

  const url = 'http://localhost:8000'

  useEffect(() => {
    getUsers()
  }, [])

  const getUsers = () => {
    axios
      .get(`${url}/users`)
      .then((res) => {
        const allUsers = res.data[0]
        console.log('allUsers', allUsers)
        getUser(allUsers)
      })
      .catch((err) => console.log(err))
  }

  function changeForm() {
    setRegisterForm(!registerForm)
    console.log('registerForm', registerForm)
  }

  const handleSubmit = async (event) => {
    console.log('registerForm', registerForm)
    event.preventDefault()
    setIsLoading(true)
    // Login
    if (!registerForm) {
      try {
        await userLogin({ dni, password })
        setIsLoading(false)
        console.log('logged in successfully')
      } catch (error) {
        setError('Invalid username or password')
        setIsLoading(false)
        setDni('')
        setPassword('')
      }
      return
    }
    // Register
    console.log('Register')
    try {
      await userRegister({ dni, name, password })
      setIsLoading(false)
      console.log('register successfully')
    } catch (error) {
      setError('Invalid data')
      setIsLoading(false)
      setDni('')
      setName('')
      setPassword('')
    }
  }

  return (
    <Container maxW="md" centerContent>
      <Heading as="h4" size="xl" align="center" mb="8">
        {!registerForm ? 'Login' : 'Register'}
      </Heading>
      <Box w="100%" borderWidth={1} borderRadius={8} boxShadow="lg" p="4">
        <form onSubmit={handleSubmit}>
          {error && <ErrorMessage message={error} />}
          {!registerForm ? (
            <Box>
              <FormControl isRequired>
                <Box mb="5">
                  <FormLabel htmlFor="dni">DNI</FormLabel>
                  <Input
                    id="dni"
                    type="number"
                    placeholder="68234665"
                    onChange={(event) => {
                      setDni(event.currentTarget.value)
                      setError('')
                    }}
                  />
                </Box>
                <Box mb="5">
                  <FormLabel htmlFor="password">Password</FormLabel>
                  <Input
                    id="password"
                    type="password"
                    placeholder="*******"
                    onChange={(event) => {
                      setPassword(event.currentTarget.value)
                      setError('')
                    }}
                  />
                </Box>
              </FormControl>
              <Button
                type="submit"
                colorScheme="teal"
                variantcolor="teal"
                variant="outline"
                width="full"
                mt={4}
              >
                {isLoading ? (
                  <CircularProgress isIndeterminate size="24px" color="teal" />
                ) : (
                  'Sign In'
                )}
              </Button>
              <Text align="center" fontSize="sm" mt="3">
                Don't have an account?{' '}
                <Link color="teal" onClick={changeForm}>
                  Register
                </Link>
              </Text>
            </Box>
          ) : (
            <Box>
              <FormControl isRequired>
                <Box mb="5">
                  <FormLabel htmlFor="dni">DNI</FormLabel>
                  <Input
                    id="dni"
                    type="number"
                    placeholder="68234665"
                    onChange={(event) => {
                      setDni(event.currentTarget.value)
                      setError('')
                    }}
                  />
                </Box>
                <Box mb="5">
                  <FormLabel htmlFor="name">Nombre</FormLabel>
                  <Input
                    id="name"
                    type="text"
                    placeholder="Jhon Doe"
                    onChange={(event) => {
                      setName(event.currentTarget.value)
                      setError('')
                    }}
                  />
                </Box>
                <Box mb="5">
                  <FormLabel htmlFor="password">Password</FormLabel>
                  <Input
                    id="password"
                    type="password"
                    placeholder="*******"
                    onChange={(event) => {
                      setPassword(event.currentTarget.value)
                      setError('')
                    }}
                  />
                </Box>
              </FormControl>
              <Button
                type="submit"
                colorScheme="teal"
                variantcolor="teal"
                variant="outline"
                width="full"
                mt={4}
              >
                {isLoading ? (
                  <CircularProgress isIndeterminate size="24px" color="teal" />
                ) : (
                  'Register'
                )}
              </Button>
              <Text align="center" fontSize="sm" mt="3">
                Have an account?{' '}
                <Link color="teal" onClick={changeForm}>
                  Login
                </Link>
              </Text>
            </Box>
          )}
        </form>
      </Box>
    </Container>
  )
}

export default LoginForm
