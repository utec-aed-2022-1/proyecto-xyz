import Head from 'next/head'
import Navbar from '../../components/Navbar'

import { Box, Container, Button, Text, VStack, Link } from '@chakra-ui/react'
import { ArrowForwardIcon } from '@chakra-ui/icons'

import { useRouter } from 'next/router'

export default function Dashboard() {
  const router = useRouter()
  const { pid } = router.query
  const dni = { pid }

  const goToWithdrawal = () => {
    router.push({
      pathname: '/withdrawal/[pid]',
      query: { pid: dni }
    })
  }

  const goToTransfer = () => {
    router.push({
      pathname: '/transfer/[pid]',
      query: { pid: dni }
    })
  }

  const goToSalesRecord = () => {
    router.push({
      pathname: '/sales-record/[pid]',
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
            <Link href="/withdrawal">
              <Button
                w="100%"
                rightIcon={<ArrowForwardIcon />}
                colorScheme="teal"
                variant="outline"
                onClick={goToWithdrawal}
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
                onClick={goToTransfer}
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
                onClick={goToSalesRecord}
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
