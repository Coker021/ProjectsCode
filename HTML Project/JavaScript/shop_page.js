let iconCart = document.getElementById('product1');
let closeCart = document.querySelector('.close');
let body = document.querySelector('body');
let listProductHTML = document.querySelector('.listProduct');


iconCart.addEventListener('click',() => {
    body.classList.toggle('showCart')
})
closeCart.addEventListener('click',() => {
    body.classList.toggle('showCart')
})

