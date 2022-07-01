import { useState } from 'react'
import {
  useColorMode,
  Switch,
  Flex,
  Button,
  IconButton,
  Heading,
  Box,
  Spacer,
  Container
} from '@chakra-ui/react'
import { HamburgerIcon, CloseIcon } from '@chakra-ui/icons'
import Link from 'next/link'

const Navbar = () => {
  const { colorMode, toggleColorMode } = useColorMode()
  const isDark = colorMode === 'dark'
  const [display, changeDisplay] = useState('none')
  return (
    <Container maxW="100%">
      <Flex>
        <Box p="4">
          <Flex top="1.5rem" left="1rem" align="center">
            <Link href="/" passHref>
              <a>
                <Heading>XYZ</Heading>
              </a>
            </Link>
          </Flex>
        </Box>
        <Spacer />
        <Box p={[4, 4, 0]}>
          <Flex top="1rem" right="1rem" align="center">
            {/* Desktop */}
            <Flex display={['none', 'none', 'flex', 'flex']}>
              <Link href="/" passHref>
                <Button
                  as="a"
                  variant="ghost"
                  aria-label="Home"
                  my={5}
                  w="100%"
                >
                  Home
                </Button>
              </Link>

              <Link href="/login" passHref>
                <Button
                  as="a"
                  variant="ghost"
                  aria-label="Login"
                  my={5}
                  mr={3}
                  w="100%"
                >
                  Login
                </Button>
              </Link>
            </Flex>

            {/* Mobile */}
            <IconButton
              aria-label="Open Menu"
              size="lg"
              mr={2}
              icon={<HamburgerIcon />}
              onClick={() => changeDisplay('flex')}
              display={['flex', 'flex', 'none', 'none']}
            />
            <Switch
              color="green"
              isChecked={isDark}
              onChange={toggleColorMode}
            />
          </Flex>
        </Box>

        {/* Mobile Content */}
        <Flex
          w="100vw"
          display={display}
          bgColor={isDark ? 'gray.800' : 'gray.50'}
          zIndex={20}
          h="100vh"
          pos="fixed"
          top="0"
          left="0"
          overflowY="auto"
          flexDir="column"
        >
          <Flex justify="flex-end">
            <IconButton
              mt={2}
              mr={2}
              aria-label="Open Menu"
              size="lg"
              icon={<CloseIcon />}
              onClick={() => changeDisplay('none')}
            />
          </Flex>

          <Flex flexDir="column" align="center">
            <Link href="/" passHref>
              <Button as="a" variant="ghost" aria-label="Home" my={5} w="100%">
                Home
              </Button>
            </Link>

            <Link href="/about" passHref>
              <Button as="a" variant="ghost" aria-label="About" my={5} w="100%">
                About
              </Button>
            </Link>

            <Link href="/contact" passHref>
              <Button
                as="a"
                variant="ghost"
                aria-label="Contact"
                my={5}
                w="100%"
              >
                Contact
              </Button>
            </Link>
          </Flex>
        </Flex>
      </Flex>
    </Container>
  )
}

export default Navbar
