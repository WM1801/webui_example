const arr_size = 512 * 1000;
const big_arr = new Uint8Array(arr_size);
big_arr[0] = 0xA1;
big_arr[arr_size - 1] = 0xA2;

function MyJS() {
  const MyInput = document.getElementById('MyInputID');
  const number = MyInput.value;
  my_function_with_response(number, 2).then((response) => {
    MyInput.value = response;
  });
}
