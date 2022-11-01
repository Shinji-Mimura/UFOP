const { MongoClient } = require("mongodb");
const stream = require("stream");

async function main() {
    const uri = "mongodb://10.158.0.4:60000/pokemons";
    const client = new MongoClient(uri);
    try {
        await client.connect();
        const pipeline = [
            {
                $match: {
                    $or: [{ operationType: "insert" }, { operationType: "delete" }],
                },
            },
        ];

        // Monitor new listings using EventEmitter's on() function.
        await monitorListingsUsingEventEmitter(client, 1000000000, pipeline);
    } finally {
        await client.close();
    }
}

main().catch(console.error);

function closeChangeStream(timeInMs = 60000, changeStream) {
    return new Promise((resolve) => {
        setTimeout(() => {
            console.log("Closing the change stream");
            changeStream.close();
            resolve();
        }, timeInMs);
    });
}

async function monitorListingsUsingEventEmitter(
    client,
    timeInMs = 60000,
    pipeline = []
) {
    const collection = client.db("pokemonsdb").collection("pokemons");
    const changeStream = collection.watch(pipeline);
    changeStream.on("change", (next) => {
        console.log(next);
        console.log("\n");
    });
    // Wait the given amount of time and then close the change stream
    await closeChangeStream(timeInMs, changeStream);
}
