import Head from 'next/head'
import Navbar from '../components/Navbar'

import { Box, Container, Heading, Image, Text } from '@chakra-ui/react'

export default function Home() {
  return (
    <div>
      <Head>
        <title>Home</title>
        <meta name="description" content="Blockchain application" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <Navbar />
      <Container maxW="2xl" centerContent>
        <Box px="4" py="10">
          <Heading as="h2" size="2xl" align="center" mb="8">
            Blockchain - Bank operations
          </Heading>
          <Text fontSize="md" align="center">
            Aplicación para crear usuarios y operaciones bancarias de manera segura usando Blockchain.
          </Text>
          <Box align="center">
            <Image
              boxSize="300px"
              objectFit="cover"
              src="https://cdni.iconscout.com/illustration/premium/thumb/blockchain-cryptocurrency-3954405-3274482.png"
              alt="blockchain"
              mx="auto"
            />
          </Box>
        </Box>
      </Container>
    </div>
  )
}
