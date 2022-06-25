import React, { useState } from 'react'

import {
  FormControl,
  FormLabel,
  Input,
  Container,
  Box,
  Button,
  CircularProgress
} from '@chakra-ui/react'

import { userLogin } from '../src/utils/loginApi'
import ErrorMessage from './ErrorMessage'

const LoginForm = () => {
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('')
  const [error, setError] = useState('')
  const [isLoading, setIsLoading] = useState(false)

  const handleSubmit = async (event) => {
    event.preventDefault()
    setIsLoading(true)
    try {
      await userLogin({ email, password })
      setIsLoading(false)
      alert('logged in successfully')
    } catch (error) {
      setError('Invalid username or password')
      setIsLoading(false)
      setEmail('')
      setPassword('')
    }
  }

  return (
    <Container maxW="md" centerContent>
      <Box w="100%" borderWidth={1} borderRadius={8} boxShadow="lg" p="4">
        <form onSubmit={handleSubmit}>
          {error && <ErrorMessage message={error} />}
          <FormControl isRequired>
            <Box mb="5">
              <FormLabel htmlFor="email">Email</FormLabel>
              <Input
                id="email"
                type="email"
                placeholder="test@test.com"
                onChange={(event) => {
                  setEmail(event.currentTarget.value)
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
        </form>
      </Box>
    </Container>
  )
}

export default LoginForm
