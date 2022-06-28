export const userLogin = async ({ email, password }) => {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (email === '12345678' && password === 'password') {
        resolve();
      } else {
        reject();
      }
    }, 3000);
  });
};