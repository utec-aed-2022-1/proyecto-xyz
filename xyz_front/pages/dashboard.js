import Head from 'next/head'
import Navbar from '../components/Navbar'

import { Box, Container, Button, Text, VStack, Link } from '@chakra-ui/react'
import { ArrowForwardIcon } from '@chakra-ui/icons'

export default function Dashboard() {
  return (
    <div>
      <Head>
        <title>Dashboard</title>
        <meta name="description" content="XYZ App" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <Navbar />
      <Container maxW="2xl" py="10" height="75vh" centerContent>
        <Text fontSize="4xl">Operations</Text>
        <Box height="100%">
          <VStack
            spacing={5}
            height="100%"
            justifyContent="center"
            alignItems="stretch"
          >
            <Link href="/withdrawal">
              <Button
                w="100%"
                rightIcon={<ArrowForwardIcon />}
                colorScheme="teal"
                variant="outline"
              >
                Withdrawal
              </Button>
            </Link>
            <Link href="/transfer">
              <Button
                w="100%"
                rightIcon={<ArrowForwardIcon />}
                colorScheme="teal"
                variant="outline"
              >
                Transfer
              </Button>
            </Link>
            <Link href="/sales-record">
              <Button
                w="100%"
                rightIcon={<ArrowForwardIcon />}
                colorScheme="teal"
                variant="outline"
              >
                Sales Record
              </Button>
            </Link>
          </VStack>
        </Box>
      </Container>
    </div>
  )
}
