function deleteCard(id) {
    var card = document.getElementById(id);
    card.style.transition = '.2s';
    card.style.opacity = '0';
    card.style.visibility = 'hidden';

    setTimeout(() => {
        card.style.display = 'none';
    }, 300);

}
