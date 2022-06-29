import Head from 'next/head'
import Navbar from '../components/Navbar'

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

export default function Transfer() {
  return (
    <div>
      <Head>
        <title>Transfer</title>
        <meta name="description" content="XYZ App" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <Navbar />
      <Box height="85vh" className="hidden-overflow">
        <Container maxW="5xl">
          <Text fontSize="2xl" align="center">
            Transfer
          </Text>
          <Flex flexWrap="wrap">
            <Box p="4">
              <b>Account number:</b> <span>1235341232</span>
              <br />
              <b>Total Amount:</b> S/<span>5000</span>
            </Box>
            <Spacer />
            <Box p="4">
              <VStack direction="row" spacing={2} align="center">
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
              </VStack>
            </Box>
          </Flex>
        </Container>
        <Container maxW="2xl" py="[5, 10]" height="100%" centerContent>
          <Text fontSize="xl" align="center" mb="1">
            History
          </Text>
          <Box width="100%" className="scroll-box" p="3">
            <Box width="100%" borderWidth="1px" borderRadius="lg" p="3" mb="4">
              <Flex flexWrap="wrap">
                <Box mx="2">
                  <Text fontWeight="bold">Amount:</Text>
                  <Text>S/123</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Operation Number:</Text>
                  <Text>6187238</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Account receiver:</Text>
                  <Text>72160454</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Date:</Text>
                  <Text>18/02/2022</Text>
                </Box>
              </Flex>
            </Box>
            <Box width="100%" borderWidth="1px" borderRadius="lg" p="3" mb="4">
              <Flex flexWrap="wrap">
                <Box mx="2">
                  <Text fontWeight="bold">Amount:</Text>
                  <Text>S/123</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Operation Number:</Text>
                  <Text>6187238</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Account receiver:</Text>
                  <Text>72160454</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Date:</Text>
                  <Text>18/02/2022</Text>
                </Box>
              </Flex>
            </Box>
            <Box width="100%" borderWidth="1px" borderRadius="lg" p="3" mb="4">
              <Flex flexWrap="wrap">
                <Box mx="2">
                  <Text fontWeight="bold">Amount:</Text>
                  <Text>S/123</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Operation Number:</Text>
                  <Text>6187238</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Account receiver:</Text>
                  <Text>72160454</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Date:</Text>
                  <Text>18/02/2022</Text>
                </Box>
              </Flex>
            </Box>
            <Box width="100%" borderWidth="1px" borderRadius="lg" p="3" mb="4">
              <Flex flexWrap="wrap">
                <Box mx="2">
                  <Text fontWeight="bold">Amount:</Text>
                  <Text>S/123</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Operation Number:</Text>
                  <Text>6187238</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Account receiver:</Text>
                  <Text>72160454</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Date:</Text>
                  <Text>18/02/2022</Text>
                </Box>
              </Flex>
            </Box>
            <Box width="100%" borderWidth="1px" borderRadius="lg" p="3" mb="4">
              <Flex flexWrap="wrap">
                <Box mx="2">
                  <Text fontWeight="bold">Amount:</Text>
                  <Text>S/123</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Operation Number:</Text>
                  <Text>6187238</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Account receiver:</Text>
                  <Text>72160454</Text>
                </Box>
                <Spacer />
                <Box mx="2">
                  <Text fontWeight="bold">Date:</Text>
                  <Text>18/02/2022</Text>
                </Box>
              </Flex>
            </Box>
          </Box>
        </Container>
      </Box>
    </div>
  )
}
