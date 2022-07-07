import React, { useEffect, useState } from 'react'
import Head from 'next/head'
import Navbar from '../../components/Navbar'
import { useForm } from 'react-hook-form'

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

export default function SaleRegister() {
  const axios = require('axios')
  const [data, setData] = useState([])
  const [error, setError] = useState('')
  const router = useRouter()
  const pid = router.query.pid

  const {
    register,
    handleSubmit,
    formState: { errors }
  } = useForm()

  const url = 'http://localhost:8000'

  useEffect(() => {
    getOperations()
  }, [])

  const getOperations = async () => {
    try {
      const response = await axios.get(
        `${url}/operations/search?type=sale_register&id_user=${pid}`
      )
      setData(response.data)
    } catch (err) {
      console.error(err)
    }
  }

  const search = async (data) => {
    try {
      const response = await axios.get(`${url}/operations/search?id_seller=${data}`)
      setData('')
      return response
    } catch (err) {
      console.error(err)
    }
  }

  const onSubmit = async (data) => {
    try {
      const result = await search(data.dni_seller)
      setData(result.data)
    } catch (error) {
      setError('error')
      setData('')
    }
  }

  return (
    <div>
      <Head>
        <title>Sale Register</title>
        <meta name="description" content="XYZ App" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <Navbar opt="dashboard" id={pid} />
      <Box height="85vh" className="hidden-overflow">
        <Container maxW="5xl">
          <Text fontSize="2xl" align="center">
            Sale Register
          </Text>
          <Flex flexWrap="wrap">
            <Box p="4">
              <b>Account number:</b> <span>{pid}</span>
              {/* <br />
              <b>Total Amount:</b> S/<span>5000</span> */}
            </Box>
            <Spacer />
            <Box p="4">
              <VStack direction="row" spacing={2} align="center">
                <form onSubmit={handleSubmit(onSubmit)}>
                  <Stack spacing={1} direction="row">
                    <Input
                      placeholder="Search by seller dni"
                      size="sm"
                      width="200px"
                      {...register('dni_seller', {
                        required: 'Please enter the dni seller'
                      })}
                    />
                    <Flex>
                      <IconButton
                        variant="outline"
                        colorScheme="teal"
                        size="sm"
                        aria-label="Search by seller dni"
                        type="submit"
                        icon={<SearchIcon />}
                      />
                    </Flex>
                  </Stack>
                </form>
              </VStack>
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
                    <Text fontWeight="bold">Account seller:</Text>
                    <Text>{dat.id_seller}</Text>
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
