import requests, base64


class PlantID:
    def __init__(self):
        self.api_key = ""
        self.headers = {"Content-Type": "application/json", "Api-Key": self.api_key}

    def auth(self):
        return requests.post("https://api.plant.id/v2/usage_info", headers=self.headers)

    def encode_image(self, images_paths):
        encoded_images = []
        for image in images_paths:
            image = open(image, "rb")
            image_bytes = image.read()
            encoded_images.append(base64.b64encode(image_bytes).decode("utf-8"))

        return encoded_images

    def identify(self, images_paths):
        encoded_images = images_paths
        results = []
        result = requests.post(
            "https://api.plant.id/v2/identify",
            headers=self.headers,
            json={"images": encoded_images},
        )
        results.append(result.text)
        return results
