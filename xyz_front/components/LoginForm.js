/* eslint-disable react/no-unescaped-entities */
import React, { useState, useEffect } from 'react'
import { useForm } from 'react-hook-form'
import { useRouter } from 'next/router'

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

const axios = require('axios')

const LoginForm = () => {
  const [data, setData] = useState('')
  const [error, setError] = useState('')
  const [isLoading, setIsLoading] = useState(false)
  const [registerForm, setRegisterForm] = useState(0)
  const router = useRouter()

  const {
    register,
    handleSubmit,
    formState: { errors }
  } = useForm()

  const url = 'http://localhost:8000'

  useEffect(() => {
    // getUsers()
  }, [])

  function changeForm() {
    setRegisterForm(!registerForm)
  }

  const userRegister = async ({ dni, name, password }) => {
    console.log('userRegister', dni, name, password)
    try {
      const response = axios.post(`${url}/user`, {
        dni: dni,
        name: name,
        password: password
      })
      setData('')
      return response
    } catch (err) {
      console.error(err)
    }
  }

  const userLogin = async ({ dni, password }) => {
    console.log('userLogin', dni, password)
    try {
      const response = axios.get(`${url}/user/${dni}`, {
        dni: dni,
        password: password
      })
      setData('')
      return response
    } catch (err) {
      console.error(err)
    }
  }

  const onSubmit = async (data) => {
    setData(data)
    if (!registerForm) {
      try {
        const result = await userLogin(data)
        setIsLoading(false)
        if (result.status) {
          console.log('login successfully')
          router.push('/dashboard')
        }
        else console.log('error')
      } catch (error) {
        setError('Invalid dni or password')
        setIsLoading(false)
        setData('')
      }
      return
    }
    try {
      const result = await userRegister(data)
      setIsLoading(false)
      if (result.status) console.log('register successfully')
      else console.log('error')
    } catch (error) {
      setError('Invalid data')
      setIsLoading(false)
      setData('')
    }
  }

  return (
    <Container maxW="md" centerContent>
      <Heading as="h4" size="xl" align="center" mb="8">
        {!registerForm ? 'Login' : 'Register'}
      </Heading>
      <Box w="100%" borderWidth={1} borderRadius={8} boxShadow="lg" p="4">
        <form onSubmit={handleSubmit(onSubmit)}>
          {/* {error && <ErrorMessage message={error} />} */}
          <Box>
            <FormControl isRequired>
              <Box mb="5">
                <FormLabel htmlFor="dni">DNI</FormLabel>
                <Input
                  id="dni"
                  type="number"
                  placeholder="68234665"
                  {...register('dni', { required: 'Please enter your dni' })}
                />
                {errors.dni && <p>{errors.dni.message}</p>}
              </Box>
              {registerForm ? (
                <Box mb="5">
                  <FormLabel htmlFor="name">Name</FormLabel>
                  <Input
                    id="name"
                    type="text"
                    placeholder="Jhonn Doe"
                    {...register('name')}
                  />
                  {errors.name && <p>{errors.name.message}</p>}
                </Box>
              ) : (
                ''
              )}
              <Box mb="5">
                <FormLabel htmlFor="password">Password</FormLabel>
                <Input
                  id="password"
                  type="password"
                  placeholder="*******"
                  {...register('password', {
                    required: 'Please enter your name'
                  })}
                />
                {errors.password && <p>{errors.password.message}</p>}
              </Box>
            </FormControl>
          </Box>
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
            ) : !registerForm ? (
              'Sign In'
            ) : (
              'Sign Up'
            )}
          </Button>
          {!registerForm ? (
            <Text align="center" fontSize="sm" mt="3">
              Don't have an account?{' '}
              <Link color="teal" onClick={changeForm}>
                Register
              </Link>
            </Text>
          ) : (
            <Text align="center" fontSize="sm" mt="3">
              Have an account?{' '}
              <Link color="teal" onClick={changeForm}>
                Login
              </Link>
            </Text>
          )}
        </form>
      </Box>
    </Container>
  )
}

export default LoginForm
