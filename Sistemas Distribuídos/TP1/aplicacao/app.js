const { MongoClient } = require("mongodb");
const stream = require("stream");
async function main() {
    pokemon_names = [
        "Pikachu",
        "Bulbasaur",
        "Charmander",
        "Charmeleon",
        "Squirtle",
        "Caterpie",
        "Metapod",
        "Blastoise",
        "Kakuna",
        "Pidgey",
        "Jigglypuff",
    ];
    pokemon_category = [
        "Eletric",
        "Water",
        "Fire",
        "Fire",
        "Water",
        "Bug",
        "Bug",
        "Water",
        "Bug",
        "Normal",
        "Normal",
    ];
    const uri = "mongodb://10.158.0.4:60000/pokemons";
    const client = new MongoClient(uri);
    try {
        await client.connect();
        const pipeline = [];
        console.log("[+] Conected\n");
        var result_delete = await client
            .db("pokemonsdb")
            .collection("pokemons")
            .deleteMany({});

        // Creating
        var id = 0;
        while (true) {
            var nomeAleatorio =
                pokemon_names[Math.floor(Math.random() * pokemon_names.length)];
            var racaAleatoria =
                pokemon_category[Math.floor(Math.random() * pokemon_category.length)];
            var pokemon = {
                name: nomeAleatorio,
                category: racaAleatoria,
                _id: id,
            };

            var result_created = await client
                .db("pokemonsdb")
                .collection("pokemons")
                .insertOne(pokemon);
            console.log(
                `[+] Pokemon created! ID: ${result_created.insertedId}, Name: ${pokemon.name}, Category: ${pokemon.category}`
            );

            var chanceDelete = Math.random();
            if (chanceDelete <= 0.25) {
                var result_delete = await client
                    .db("pokemonsdb")
                    .collection("pokemons")
                    .deleteOne({ _id: result_created.insertedId });
                console.log(`[!] ${result_delete.deletedCount} Documents Deleted.`);
            }
            console.log("\n");

            id += 1;
            await sleep(2000);
        }
    } finally {
        await client.close();
    }
}

main().catch(console.error);

function closeChangeStream(timeInMs = 60000, changeStream) {
    return new Promise((resolve) => {
        setTimeout(() => {
            console.log("[!] Closing the change stream");
            changeStream.close();
            resolve();
        }, timeInMs);
    });
}

function sleep(ms) {
    return new Promise((resolve) => {
        setTimeout(resolve, ms);
    });
}
