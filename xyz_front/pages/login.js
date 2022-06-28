import Head from 'next/head'
import Navbar from '../components/Navbar'
import LoginForm from '../components/LoginForm'

import { Container } from '@chakra-ui/react'

export default function Login() {
  return (
    <div>
      <Head>
        <title>Login</title>
        <meta name="description" content="XYZ App" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <Navbar />
      <Container maxW="2xl" py="10" centerContent>
        <LoginForm />
      </Container>
    </div>
  )
}
