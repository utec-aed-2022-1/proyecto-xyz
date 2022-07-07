import Head from 'next/head'
import Navbar from '../../components/Navbar'

import { Box, Container, Button, Text, VStack } from '@chakra-ui/react'
import { ArrowForwardIcon } from '@chakra-ui/icons'

import { useRouter } from 'next/router'

export default function Dashboard() {
  const router = useRouter()
  const pid = router.query.pid
  const name = router.query.name
  const dni = pid

  const goToView = (view) => {
    router.push({
      pathname: `/${view}/[pid]`,
      query: { pid: dni }
    })
  }

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
        <Text fontSize="2xl">User: {pid}</Text>
        <Box height="100%">
          <VStack
            spacing={5}
            height="100%"
            justifyContent="center"
            alignItems="stretch"
          >
            <Button
              w="100%"
              rightIcon={<ArrowForwardIcon />}
              colorScheme="teal"
              variant="outline"
              onClick={() => {
                goToView('withdrawal')
              }}
            >
              Withdrawal
            </Button>
            <Button
              w="100%"
              rightIcon={<ArrowForwardIcon />}
              colorScheme="teal"
              variant="outline"
              onClick={() => {
                goToView('transfer')
              }}
            >
              Transfer
            </Button>
            <Button
              w="100%"
              rightIcon={<ArrowForwardIcon />}
              colorScheme="teal"
              variant="outline"
              onClick={() => {
                goToView('sales-record')
              }}
            >
              Sales Record
            </Button>
          </VStack>
          <VStack justifyContent="center" alignItems="stretch">
            <Button
              w="100%"
              rightIcon={<ArrowForwardIcon />}
              colorScheme="teal"
              variant="outline"
              onClick={() => {
                goToView('operation')
              }}
            >
              Add Operation
            </Button>
          </VStack>
        </Box>
      </Container>
    </div>
  )
}
