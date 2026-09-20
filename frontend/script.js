let currentUserId = 1;


// ======================================
// SHOW PRODUCTS
// ======================================

function showProducts() {

    document.getElementById("products").scrollIntoView();
}


// ======================================
// REGISTER
// ======================================

async function register() {

    let name =
        document.getElementById("registerName").value;

    let email =
        document.getElementById("registerEmail").value;

    let password =
        document.getElementById("registerPassword").value;


    if (name == "" || email == "" || password == "") {

        alert("Please fill all fields");

        return;
    }


    try {

        let response = await fetch(
            "/api/v1/auth/register",
            {
                method: "POST",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify({

                    name: name,

                    email: email,

                    password: password,

                    role: "BUYER"

                })
            }
        );


        let data =
            await response.json();


        if (data.success) {

            alert("Registration successful!");

        }
        else {

            alert("Registration failed");
        }

    }
    catch (error) {

        alert("Backend server is not running");
    }
}


// ======================================
// LOGIN
// ======================================

async function login() {

    let email =
        document.getElementById("loginEmail").value;

    let password =
        document.getElementById("loginPassword").value;


    if (email == "" || password == "") {

        alert("Please enter email and password");

        return;
    }


    try {

        let response = await fetch(
            "/api/v1/auth/login",
            {
                method: "POST",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify({

                    email: email,

                    password: password

                })
            }
        );


        let data =
            await response.json();


        if (data.success) {

            alert("Login successful!");

        }
        else {

            alert("Invalid email or password");
        }

    }
    catch (error) {

        alert("Backend server is not running");
    }
}


// ======================================
// LOAD PRODUCTS
// ======================================

async function loadProducts() {

    try {

        let response =
            await fetch("/api/v1/products");

        let data =
            await response.json();

        let productList =
            document.getElementById("productList");

        productList.innerHTML = "";


        if (!data.success) {

            productList.innerHTML =
                "<p>Products could not be loaded.</p>";

            return;
        }


        for (let product of data.data) {

            let productDiv =
                document.createElement("div");

            productDiv.className =
                "product";


            productDiv.innerHTML = `

                <h3>${product.name}</h3>

                <p>${product.category}</p>

                <p>${product.description}</p>

                <p>₹${product.price}</p>

                <p>Stock: ${product.stock}</p>

                <button
                    onclick="addToCart(${product.id})">
                    Add to Cart
                </button>

            `;


            productList.appendChild(productDiv);
        }

    }
    catch (error) {

        document.getElementById("productList").innerHTML =
            "<p>Unable to connect to backend.</p>";
    }
}


// ======================================
// ADD TO CART
// ======================================

async function addToCart(productId) {

    try {

        let response = await fetch(
            "/api/v1/cart/items",
            {
                method: "POST",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify({

                    buyerId: currentUserId,

                    productId: productId,

                    quantity: 1

                })
            }
        );


        let data =
            await response.json();


        if (data.success) {

            alert("Product added to cart!");

            loadCart();

        }
        else {

            alert("Could not add product to cart");
        }

    }
    catch (error) {

        alert("Backend server is not running");
    }
}


// ======================================
// LOAD CART
// ======================================

async function loadCart() {

    try {

        let cartResponse =
            await fetch(
                "/api/v1/cart/" + currentUserId
            );


        let cartData =
            await cartResponse.json();


        let cartMessage =
            document.getElementById("cartMessage");


        if (
            !cartData.success ||
            cartData.data.length == 0
        ) {

            cartMessage.innerHTML =
                "<p>Your cart is empty.</p>";

            return;
        }


        let productResponse =
            await fetch("/api/v1/products");


        let productData =
            await productResponse.json();


        cartMessage.innerHTML = "";

        let grandTotal = 0;


        for (let item of cartData.data) {

            let product =
                productData.data.find(
                    p => p.id == item.productId
                );


            if (!product) {

                continue;
            }


            let total =
                product.price * item.quantity;


            grandTotal =
                grandTotal + total;


            let itemDiv =
                document.createElement("div");

            itemDiv.className =
                "product";


            itemDiv.innerHTML = `

                <h3>${product.name}</h3>

                <p>Price: ₹${product.price}</p>

                <p>Quantity: ${item.quantity}</p>

                <p>Total: ₹${total}</p>

            `;


            cartMessage.appendChild(itemDiv);
        }


        let totalDiv =
            document.createElement("div");


        totalDiv.innerHTML = `

            <h2>
                Grand Total: ₹${grandTotal}
            </h2>

        `;


        cartMessage.appendChild(totalDiv);


        let checkoutButton =
            document.createElement("button");


        checkoutButton.innerText =
            "Checkout";


        checkoutButton.onclick =
            function () {

                checkout(grandTotal);

            };


        cartMessage.appendChild(
            checkoutButton
        );

    }
    catch (error) {

        document.getElementById("cartMessage").innerText =
            "Unable to load cart.";
    }
}


// ======================================
// CHECKOUT
// ======================================

async function checkout(totalAmount) {

    try {

        let orderResponse =
            await fetch(
                "/api/v1/orders",
                {
                    method: "POST",

                    headers: {
                        "Content-Type": "application/json"
                    },

                    body: JSON.stringify({

                        buyerId: currentUserId,

                        totalAmount: totalAmount

                    })
                }
            );


        let orderData =
            await orderResponse.json();


        if (!orderData.success) {

            alert("Order creation failed");

            return;
        }


        alert("Order created successfully!");


        let historyResponse =
            await fetch(
                "/api/v1/orders/" + currentUserId
            );


        let historyData =
            await historyResponse.json();


        if (
            !historyData.success ||
            historyData.data.length == 0
        ) {

            alert(
                "Order created, but order ID was not found."
            );

            return;
        }


        let orders =
            historyData.data;


        let latestOrder =
            orders[orders.length - 1];


        let orderId =
            latestOrder.id;


        let paymentResponse =
            await fetch(
                "/api/v1/orders/payment",
                {
                    method: "PUT",

                    headers: {
                        "Content-Type": "application/json"
                    },

                    body: JSON.stringify({

                        orderId: orderId,

                        paymentStatus: "PAID"

                    })
                }
            );


        let paymentData =
            await paymentResponse.json();


        if (paymentData.success) {

            alert(
                "Mock payment successful! Order ID: " +
                orderId
            );


            loadCart();

            loadOrders();

        }
        else {

            alert("Payment failed");
        }

    }
    catch (error) {

        alert("Checkout failed");
    }
}


// ======================================
// LOAD ORDERS
// ======================================

async function loadOrders() {

    try {

        let response =
            await fetch(
                "/api/v1/orders/" + currentUserId
            );


        let data =
            await response.json();


        let orderList =
            document.getElementById("orderList");


        orderList.innerHTML = "";


        if (
            !data.success ||
            data.data.length == 0
        ) {

            orderList.innerHTML =
                "<p>No orders yet.</p>";

            return;
        }


        for (let order of data.data) {

            let orderDiv =
                document.createElement("div");


            orderDiv.className =
                "product";


            orderDiv.innerHTML = `

                <h3>
                    Order ID: ${order.id}
                </h3>

                <p>
                    Total: ₹${order.totalAmount}
                </p>

                <p>
                    Status: ${order.status}
                </p>

                <p>
                    Payment: ${order.paymentStatus}
                </p>

            `;


            orderList.appendChild(orderDiv);
        }

    }
    catch (error) {

        document.getElementById("orderList").innerHTML =
            "<p>Unable to load orders.</p>";
    }
}


// ======================================
// ADD REVIEW
// ======================================

async function addReview() {

    let productId =
        document.getElementById("reviewProductId").value;


    let rating =
        document.getElementById("reviewRating").value;


    let comment =
        document.getElementById("reviewComment").value;


    if (
        productId == "" ||
        rating == "" ||
        comment == ""
    ) {

        alert("Please fill all review fields");

        return;
    }


    if (rating < 1 || rating > 5) {

        alert("Rating must be between 1 and 5");

        return;
    }


    try {

        let response =
            await fetch(
                "/api/v1/reviews",
                {
                    method: "POST",

                    headers: {
                        "Content-Type": "application/json"
                    },

                    body: JSON.stringify({

                        productId: Number(productId),

                        buyerId: currentUserId,

                        rating: Number(rating),

                        comment: comment

                    })
                }
            );


        let data =
            await response.json();


        if (data.success) {

            alert(
                "Review submitted successfully!"
            );

            loadReviews();

        }
        else {

            alert(
                "Review submission failed"
            );
        }

    }
    catch (error) {

        alert("Unable to connect to backend");
    }
}


// ======================================
// LOAD REVIEWS
// ======================================

async function loadReviews() {

    let productId =
        document.getElementById("reviewProductId").value;


    if (productId == "") {

        alert("Please enter Product ID");

        return;
    }


    try {

        let response =
            await fetch(
                "/api/v1/reviews/" + productId
            );


        let data =
            await response.json();


        let reviewList =
            document.getElementById("reviewList");


        reviewList.innerHTML = "";


        if (
            !data.success ||
            data.data.length == 0
        ) {

            reviewList.innerHTML =
                "<p>No reviews found.</p>";

            return;
        }


        for (let review of data.data) {

            let reviewDiv =
                document.createElement("div");


            reviewDiv.className =
                "review";


            reviewDiv.innerHTML = `

                <h3>
                    ⭐ ${review.rating}/5
                </h3>

                <p>
                    ${review.comment}
                </p>

                <p>
                    Buyer ID: ${review.buyerId}
                </p>

            `;


            reviewList.appendChild(reviewDiv);
        }

    }
    catch (error) {

        document.getElementById("reviewList").innerHTML =
            "<p>Unable to load reviews.</p>";
    }
}


// ======================================
// ADMIN - VIEW USERS
// ======================================

async function loadAdminUsers() {

    try {

        let response =
            await fetch(
                "/api/v1/admin/users"
            );


        let data =
            await response.json();


        let container =
            document.getElementById("adminUsers");


        container.innerHTML =
            "<h3>Users</h3>";


        if (
            !data.success ||
            data.data.length == 0
        ) {

            container.innerHTML +=
                "<p>No users found.</p>";

            return;
        }


        for (let user of data.data) {

            let box =
                document.createElement("div");


            box.className =
                "admin-box";


            box.innerHTML = `

                <h3>
                    User ID: ${user.id}
                </h3>

                <p>
                    Name: ${user.name}
                </p>

                <p>
                    Email: ${user.email}
                </p>

                <p>
                    Role: ${user.role}
                </p>

                <button
                    class="admin-delete"
                    onclick="deleteAdminUser(${user.id})">

                    Delete User

                </button>

            `;


            container.appendChild(box);
        }

    }
    catch (error) {

        alert("Unable to load admin users");
    }
}


// ======================================
// ADMIN - DELETE USER
// ======================================

async function deleteAdminUser(userId) {

    if (
        !confirm(
            "Are you sure you want to delete this user?"
        )
    ) {

        return;
    }


    try {

        let response =
            await fetch(
                "/api/v1/admin/users/" + userId,
                {
                    method: "DELETE"
                }
            );


        let data =
            await response.json();


        if (data.success) {

            alert("User deleted successfully!");

            loadAdminUsers();

        }
        else {

            alert("User deletion failed");
        }

    }
    catch (error) {

        alert("Unable to delete user");
    }
}


// ======================================
// ADMIN - VIEW PRODUCTS
// ======================================

async function loadAdminProducts() {

    try {

        let response =
            await fetch(
                "/api/v1/admin/products"
            );


        let data =
            await response.json();


        let container =
            document.getElementById("adminProducts");


        container.innerHTML =
            "<h3>Products</h3>";


        if (
            !data.success ||
            data.data.length == 0
        ) {

            container.innerHTML +=
                "<p>No products found.</p>";

            return;
        }


        for (let product of data.data) {

            let box =
                document.createElement("div");


            box.className =
                "admin-box";


            box.innerHTML = `

                <h3>
                    Product ID: ${product.id}
                </h3>

                <p>
                    Name: ${product.name}
                </p>

                <p>
                    Seller ID: ${product.sellerId}
                </p>

                <p>
                    Price: ₹${product.price}
                </p>

                <p>
                    Stock: ${product.stock}
                </p>

                <p>
                    Category: ${product.category}
                </p>

                <button
                    class="admin-delete"
                    onclick="deleteAdminProduct(${product.id})">

                    Delete Product

                </button>

            `;


            container.appendChild(box);
        }

    }
    catch (error) {

        alert("Unable to load admin products");
    }
}


// ======================================
// ADMIN - DELETE PRODUCT
// ======================================

async function deleteAdminProduct(productId) {

    if (
        !confirm(
            "Are you sure you want to delete this product?"
        )
    ) {

        return;
    }


    try {

        let response =
            await fetch(
                "/api/v1/admin/products/" + productId,
                {
                    method: "DELETE"
                }
            );


        let data =
            await response.json();


        if (data.success) {

            alert(
                "Product deleted successfully!"
            );

            loadAdminProducts();

            loadProducts();

        }
        else {

            alert("Product deletion failed");
        }

    }
    catch (error) {

        alert("Unable to delete product");
    }
}


// ======================================
// ADMIN - VIEW ORDERS
// ======================================

async function loadAdminOrders() {

    try {

        let response =
            await fetch(
                "/api/v1/admin/orders"
            );


        let data =
            await response.json();


        let container =
            document.getElementById("adminOrders");


        container.innerHTML =
            "<h3>Orders</h3>";


        if (
            !data.success ||
            data.data.length == 0
        ) {

            container.innerHTML +=
                "<p>No orders found.</p>";

            return;
        }


        for (let order of data.data) {

            let box =
                document.createElement("div");


            box.className =
                "admin-box";


            box.innerHTML = `

                <h3>
                    Order ID: ${order.id}
                </h3>

                <p>
                    Buyer ID: ${order.buyerId}
                </p>

                <p>
                    Total: ₹${order.totalAmount}
                </p>

                <p>
                    Status: ${order.status}
                </p>

                <p>
                    Payment: ${order.paymentStatus}
                </p>

            `;


            container.appendChild(box);
        }

    }
    catch (error) {

        alert("Unable to load admin orders");
    }
}


// ======================================
// AI CHATBOT
// ======================================

function addChatMessage(message, type) {

    let chatBox =
        document.getElementById("chatBox");


    let messageDiv =
        document.createElement("div");


    if (type == "user") {

        messageDiv.className =
            "user-message";

    }
    else {

        messageDiv.className =
            "bot-message";
    }


    messageDiv.innerText =
        message;


    chatBox.appendChild(messageDiv);


    chatBox.scrollTop =
        chatBox.scrollHeight;
}


// ======================================
// SEND CHAT MESSAGE
// ======================================

function sendMessage() {

    let input =
        document.getElementById("chatInput");


    let message =
        input.value.trim();


    if (message == "") {

        return;
    }


    addChatMessage(
        message,
        "user"
    );


    input.value = "";


    let lowerMessage =
        message.toLowerCase();


    let reply =
        "";


    if (
        lowerMessage.includes("hello") ||
        lowerMessage.includes("hi") ||
        lowerMessage.includes("hey")
    ) {

        reply =
            "Hello! Welcome to DharaniMart. How can I help you?";

    }

    else if (
        lowerMessage.includes("product") ||
        lowerMessage.includes("products")
    ) {

        reply =
            "You can view available products in the Products section.";

    }

    else if (
        lowerMessage.includes("cart")
    ) {

        reply =
            "You can add products to your shopping cart and view the total amount in the Cart section.";

    }

    else if (
        lowerMessage.includes("order")
    ) {

        reply =
            "You can check your previous orders in the Order History section.";

    }

    else if (
        lowerMessage.includes("payment")
    ) {

        reply =
            "DharaniMart currently supports a mock payment confirmation for testing.";

    }

    else if (
        lowerMessage.includes("review") ||
        lowerMessage.includes("rating")
    ) {

        reply =
            "You can submit a product rating from the Product Reviews & Ratings section.";

    }

    else if (
        lowerMessage.includes("admin")
    ) {

        reply =
            "The Admin section allows management of users, products and orders.";

    }

    else if (
        lowerMessage.includes("price")
    ) {

        reply =
            "You can check the price of each product in the Products section.";

    }

    else {

        reply =
            "Sorry, I can currently help with products, cart, orders, payments, reviews and DharaniMart features.";

    }


    setTimeout(
        function () {

            addChatMessage(
                reply,
                "bot"
            );

        },
        400
    );
}


// ======================================
// ENTER KEY FOR CHATBOT
// ======================================

function handleChatKey(event) {

    if (event.key === "Enter") {

        sendMessage();

    }
}


// ======================================
// LOAD EVERYTHING
// ======================================

loadProducts();

loadCart();

loadOrders();