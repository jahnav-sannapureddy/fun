let board;
let context;
let boardWidth = 500;
let boardHeight = 500; 


const paddleHeight = 20;
const paddleWidth = 110;
const paddleSpeed = 12;

const paddle = {
    x: boardWidth/2 - paddleWidth/2,
    y: boardHeight - paddleHeight - 10,
    width: paddleWidth,
    height: paddleHeight,
    speed: paddleSpeed,
}

window.onload = () => {
    board = document.getElementById("gameboard");
    board.width = boardWidth;
    board.height = boardHeight;
    context = board.getContext("2d");

    context.fillStyle = "blue";
    context.fillRect(paddle.x, paddle.y, paddle.width, paddle.height);

    document.addEventListener("keydown", movePaddle);

    requestAnimationFrame(update);
}

const movePaddle = (e) => {
    console.log(e)
    if(e.code == "ArrowLeft"){
        if( paddle.x > 0){
            paddle.x -= paddle.speed;
        }
    }
    else if(e.code == "ArrowRight"){
        if(paddle.x < boardWidth-paddleWidth){
            paddle.x += paddle.speed;
        }
    }
}
const update = () => {
    requestAnimationFrame(update);

    context.clearRect(0, 0, boardWidth, boardHeight);

    context.fillStyle = "lightgreen";
    context.fillRect(paddle.x, paddle.y, paddle.width, paddle.height);
}