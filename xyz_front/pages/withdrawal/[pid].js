import React, { useEffect, useState } from 'react'
import Head from 'next/head'
import Navbar from '../../components/Navbar'

import {
  Box,
  Container,
  Text,
  VStack,
  Flex,
  Spacer,
  Stack,
  Input,
  IconButton
} from '@chakra-ui/react'
import { SearchIcon } from '@chakra-ui/icons'

import { useRouter } from 'next/router'

export default function Withdrawal() {
  const axios = require('axios')
  const [data, setData] = useState([])
  const router = useRouter()
  const pid = router.query.pid

  const url = 'http://localhost:8000'

  useEffect(() => {
    getOperations()
  }, [])

  const getOperations = async () => {
    try {
      const response = await axios.get(
        `${url}/operations/search?type=withdrawal&id_user=${pid}`
      )
      setData(response.data)
    } catch (err) {
      console.error(err)
    }
  }

  return (
    <div>
      <Head>
        <title>Withdrawal</title>
        <meta name="description" content="XYZ App" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <Navbar opt="dashboard" id={pid} />
      <Box height="85vh" className="hidden-overflow">
        <Container maxW="5xl">
          <Text fontSize="2xl" align="center">
            Withdrawal
          </Text>
          <Flex flexWrap="wrap">
            <Box p="4">
              <b>Account number:</b> <span>{pid}</span>
              {/* <br />
              <b>Total Amount:</b> S/<span>5000</span> */}
            </Box>
            <Spacer />
            <Box p="4">
              {/* <VStack direction="row" spacing={2} align="center">
                <Stack spacing={1} direction="row">
                  <Input placeholder="Search by date" size="sm" width="200px" />
                  <Flex>
                    <IconButton
                      variant="outline"
                      colorScheme="teal"
                      size="sm"
                      aria-label="Search by date"
                      icon={<SearchIcon />}
                    />
                  </Flex>
                </Stack>
                <Stack spacing={1} direction="row">
                  <Input
                    placeholder="Search by operation number"
                    size="sm"
                    width="200px"
                  />
                  <Flex>
                    <IconButton
                      variant="outline"
                      colorScheme="teal"
                      size="sm"
                      aria-label="Search by operation number"
                      icon={<SearchIcon />}
                    />
                  </Flex>
                </Stack>
              </VStack> */}
            </Box>
          </Flex>
        </Container>
        <Container maxW="2xl" py="[5, 10]" height="100%" centerContent>
          <Text fontSize="xl" align="center" mb="1">
            History
          </Text>
          <Box width="100%" className="scroll-box" p="3">
            {data.map((dat) => (
              <Box
                key={dat.id}
                width="100%"
                borderWidth="1px"
                borderRadius="lg"
                p="3"
                mb="4"
              >
                <Flex flexWrap="wrap">
                  <Box mx="2">
                    <Text fontWeight="bold">Amount:</Text>
                    <Text>S/{dat.amount}</Text>
                  </Box>
                  <Spacer />
                  <Box mx="2">
                    <Text fontWeight="bold">Date:</Text>
                    <Text>{dat.date}</Text>
                  </Box>
                </Flex>
              </Box>
            ))}
          </Box>
        </Container>
      </Box>
    </div>
  )
}
