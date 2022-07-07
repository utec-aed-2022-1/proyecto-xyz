import React, { useState, useEffect } from 'react'
import { useForm } from 'react-hook-form'
import { Select } from '@chakra-ui/react'

import Navbar from '../../components/Navbar'

import {
  FormControl,
  FormLabel,
  Input,
  Container,
  Box,
  Button,
  CircularProgress,
  Heading,
  useToast
} from '@chakra-ui/react'
import Head from 'next/head'

import { useRouter } from 'next/router'

const axios = require('axios')

const Operation = () => {
  const router = useRouter()
  
  const pid = router.query.pid
  const dni = pid

  const [data, setData] = useState('')
  const [operationType, setOperationType] = useState('')
  const [error, setError] = useState('')
  const [isLoading, setIsLoading] = useState(false)
  const toast = useToast()

  const url = 'http://localhost:8000'

  const {
    register,
    handleSubmit,
    formState: { errors }
  } = useForm()

  const operationHandler = (event) => {
    setOperationType(event.target.value)
  }

  const addOperation = async (data) => {
    if (data.operationType === 'transfer') {
      try {
        const response = axios.post(`${url}/operation`, {
          amount: parseInt(data.amount),
          date: data.date,
          id_sender: data.dni,
          id_user: data.dni,
          id_receiver: data.dniReceiver,
          type: data.operationType
        })
        setData('')
        return response
      } catch (err) {
        console.error(err)
      }
      return
    }

    if (data.operationType === 'sale_register') {
      try {
        const response = axios.post(`${url}/operation`, {
          amount: parseInt(data.amount),
          date: data.date,
          id_client: data.dni,
          id_user: data.dni,
          id_seller: data.dniSeller,
          type: data.operationType
        })
        setData('')
        return response
      } catch (err) {
        console.error(err)
      }
      return
    }

    try {
      const response = axios.post(`${url}/operation`, {
        amount: parseInt(data.amount),
        date: data.date,
        id_client: data.dni,
        id_user: data.dni,
        type: data.operationType
      })
      setData('')
      return response
    } catch (err) {
      console.error(err)
    }
  }

  const onSubmit = async (data) => {
    setData(data)
    try {
      const result = await addOperation(data)
      setIsLoading(false)
      if (result.status !== 200) {
        toast({
          title: 'Error',
          status: 'error',
          position: 'top',
          duration: 3000,
          isClosable: true
        })
        return
      }

      if (data.operationType === 'transfer') {
        toast({
          title: 'Transfer registered',
          status: 'success',
          position: 'top',
          duration: 3000,
          isClosable: true
        })
        return
      }

      if (data.operationType === 'sale_register') {
        toast({
          title: 'Sales registered',
          status: 'success',
          position: 'top',
          duration: 3000,
          isClosable: true
        })
        return
      }

      toast({
        title: 'Withdrawal registered',
        status: 'success',
        position: 'top',
        duration: 3000,
        isClosable: true
      })
    } catch (error) {
      setError('Invalid dni or password')
      setIsLoading(false)
      setData('')
    }
  }

  return (
    <div>
      <Head>
        <title>Operations</title>
        <meta name="description" content="XYZ App" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <Navbar opt="dashboard" id={dni} />

      <Container maxW="md" centerContent py={[0, 10]}>
        <Heading as="h5" size="lg" align="center" mb="8">
          Add Operation
        </Heading>
        <Box w="100%" borderWidth={1} borderRadius={8} boxShadow="lg" p="4">
          <form onSubmit={handleSubmit(onSubmit)}>
            <Box>
              <FormControl isRequired>
                <Box mb="5">
                  <FormLabel htmlFor="password">Operation type</FormLabel>
                  <Select
                    value={operationType}
                    {...register('operationType', {
                      required: 'Please select the type of operation'
                    })}
                    onChange={operationHandler}
                  >
                    <option value="">--Choose and option--</option>
                    <option value="withdrawal">withdrawal</option>
                    <option value="transfer">transfer</option>
                    <option value="sale_register">sale register</option>
                  </Select>
                </Box>
                <Box mb="5">
                  <FormLabel htmlFor="date">Date</FormLabel>
                  <Input
                    id="date"
                    type="date"
                    placeholder="18/02/2001"
                    {...register('date', { required: 'Please enter the date' })}
                  />
                </Box>
                <Box mb="5">
                  <FormLabel htmlFor="dni">DNI</FormLabel>
                  <Input
                    id="dni"
                    type="number"
                    placeholder="87654321"
                    {...register('dni', { required: 'Please enter your dni' })}
                  />
                </Box>
                {operationType === 'transfer' ? (
                  <Box mb="5">
                    <FormLabel htmlFor="dniReceiver">DNI receiver</FormLabel>
                    <Input
                      id="dniReceiver"
                      type="number"
                      placeholder="87654321"
                      {...register('dniReceiver', {
                        required: 'Please enter the dni receiver'
                      })}
                    />
                  </Box>
                ) : (
                  ''
                )}
                {operationType === 'sale_register' ? (
                  <Box mb="5">
                    <FormLabel htmlFor="dniSeller">DNI seller</FormLabel>
                    <Input
                      id="dniSeller"
                      type="number"
                      placeholder="87654321"
                      {...register('dniSeller', {
                        required: 'Please enter the dni seller'
                      })}
                    />
                  </Box>
                ) : (
                  ''
                )}
                <Box mb="5">
                  <FormLabel htmlFor="amount">Amount</FormLabel>
                  <Input
                    id="amount"
                    type="number"
                    placeholder="500"
                    {...register('amount', {
                      required: 'Please enter the amount'
                    })}
                  />
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
              ) : !true ? (
                'Guardar'
              ) : (
                'Guardar'
              )}
            </Button>
          </form>
        </Box>
      </Container>
    </div>
  )
}

export default Operation
