const arr_size = 512 * 1000;
const big_arr = new Uint8Array(arr_size);
big_arr[0] = 0xA1;
big_arr[arr_size - 1] = 0xA2;

let count = 0; 
let timerId = 0; 
let runTimer = 0; 

function MyJS() {
  const MyInput = document.getElementById('MyInputID');
  const number = MyInput.value;
  my_function_with_response(number, 2).then((response) => {
    MyInput.value = response;
  });
}

function GetCount() {
  return count; 
}

function SetCount(number)
{
  document.getElementById('count').innerHTML = number;
  count = number; 
}

function AutoTest(number) {
  if(runTimer == 0) {
    timerId = setInterval(function() {my_function_count(); }, 10);
    runTimer = 1; 
  }
  else {
    runTimer = 0; 
    clearInterval(timerId); 
  }

}
